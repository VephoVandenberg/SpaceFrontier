#include <glm/gtx/vector_angle.hpp>

#include "../../include/enemies/enemy.h"
#include "../../include/player.h"

#include "../../../system/include/texture.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_enemyVelocityCoeff = 350.0f;
constexpr float g_attackRange = 600.0f;
constexpr float g_deltaAngle = 1.5f;
constexpr float g_PI = 3.14159265359f;
constexpr float g_borderAddition = 200.0f;
constexpr glm::vec3 g_projSize = { 2.0f, 15.0f, 0.0f };

Enemy::Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
	, m_health(3)
	, m_timer(0.0f)
	, m_state(EnemyState::Idle)
{
	m_velocity.x = glm::sin(m_angle) * g_enemyVelocityCoeff;
	m_velocity.y = -glm::cos(m_angle) * g_enemyVelocityCoeff;
}

void Enemy::update(float dt, float borderX, float borderY, const glm::vec3& cameraPos, const Player& player)
{
	m_timer += dt;

	// Enemy's primitive ai
	switch (m_state)
	{

	case EnemyState::Idle:
		idle(dt, player);
		break;

	case EnemyState::Patrolling:
		patroll(dt, player);
		break;

	case EnemyState::Fighting:
		fight(dt, player);
		break;

	case EnemyState::Fleeing:
		flee(dt, player);
		break;
	}

	// Projectiles update
	for (auto& proj : m_projectiles)
	{
		proj.update(dt);
	}

	if (!m_projectiles.empty() &&
		m_projectiles.back().isOut(
			cameraPos.x - g_borderAddition, cameraPos.x + borderX + g_borderAddition,
			cameraPos.y - g_borderAddition, cameraPos.y + borderY + g_borderAddition))
	{
		m_projectiles.pop_front();
	}
}

void Enemy::idle(float dt, const Player& player)
{
	if (m_timer >= 3.0f)
	{
		m_state = EnemyState::Patrolling;
		m_timer = 0.0f;

		m_velocity *= -1;
	}

	if (glm::length(player.getPos() - m_pos) <= g_attackRange)
	{
		m_state = EnemyState::Fighting;
		m_shootingTimeGap = static_cast<float>(std::rand() % 2 + 1);
		m_timer = 0.0f;
	}
}

void Enemy::patroll(float dt, const Player& player)
{
	if (m_timer >= 3.0f)
	{
		m_state = EnemyState::Idle;
		m_timer = 0.0f;
	}

	if (glm::length(player.getPos() - m_pos) <= g_attackRange)
	{
		m_state = EnemyState::Fighting;
		m_shootingTimeGap = static_cast<float>(std::rand() % 2 + 1);
		m_timer = 0.0f;
	}

	m_pos += m_velocity * dt;
}

void Enemy::fight(float dt, const Player& player)
{
	glm::vec2 normVel = glm::normalize(m_velocity);
	glm::vec2 normVelPlayer = glm::normalize(player.getVelocity());
	glm::vec2 normEnemyToPlayer = glm::normalize(player.getPos() + player.getScale() / 4.0f - m_pos);
	float dotAttack = glm::dot(normVel, normEnemyToPlayer);
	float dotChase = glm::dot(normVel, normVelPlayer);

	if (dotAttack < 0.995f)
	{
		float angle = glm::orientedAngle(normVel, normEnemyToPlayer) * (180.0f / g_PI);
		if (angle < 0.0f)
		{
			m_angle -= g_deltaAngle * dt;
		}
		else
		{
			m_angle += g_deltaAngle * dt;
		}
		m_velocity.x = glm::sin(m_angle) * g_enemyVelocityCoeff;
		m_velocity.y = -glm::cos(m_angle) * g_enemyVelocityCoeff;
		m_timer = 0.0f;
	}

	if (m_timer >= m_shootingTimeGap && dotAttack >= 0.895f)
	{
		shoot();
		m_timer = 0.0f;
	}

	/*
	if (glm::length(player.getPos() - m_pos) >= g_attackRange - 200.0f)
	{
		if (dotChase >= 0.9f)
		{
			m_pos += m_velocity * dt;
		}
		else
		{
			float angle = glm::orientedAngle(normVel, normEnemyToPlayer) * (180.0f / g_PI);
			if (angle < 0.0f)
			{
				m_angle -= 2.0f*g_deltaAngle * dt;
			}
			else
			{
				m_angle += 2.0f*g_deltaAngle * dt;
			}
			m_velocity.x = glm::sin(m_angle) * g_enemyVelocityCoeff;
			m_velocity.y = -glm::cos(m_angle) * g_enemyVelocityCoeff;
		}
	}
	*/
	if (glm::length(player.getPos() - m_pos) >= g_attackRange - 200.0f)
	{
		m_pos += m_velocity * dt;
	}

	m_velocity *= 0.995f;

	if (glm::length(player.getPos() - m_pos) >= g_attackRange + 100.0f)
	{
		m_state = EnemyState::Idle;
	}

	if (m_health == 1)
	{
		m_state = EnemyState::Fleeing;
	}
}


void Enemy::flee(float dt, const Player& player)
{
	m_pos -= m_velocity * dt;

	if (glm::length(player.getPos() - m_pos) < g_attackRange)
	{
		m_state = EnemyState::Idle;
		m_timer = 0.0f;
	}
}

void Enemy::shoot()
{
	glm::vec3 projPos = glm::vec3(m_pos.x + m_scale.x / 2.0f, m_pos.y + m_scale.y / 3.0f, 0.0f);
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
	m_projectiles.push_back(Projectile(projPos, g_projSize, color, m_velocity, m_angle));
}

void Enemy::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader, m_texture);
}

void Enemy::drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	for (auto& proj : m_projectiles)
	{
		proj.draw(shader, renderer, cameraPos);
	}
}

int Enemy::checkProjPlayerCoollision(const Player& player)
{
	int damage = 0;
	m_projectiles.erase(
		std::remove_if(
			m_projectiles.begin(),
			m_projectiles.end(),
			[&](const Projectile& proj) {
				if (proj.checkCollision(player))
				{
					damage++;
					return true;
				}
				return false;
			}),
		m_projectiles.end());

	return damage;
}

void Enemy::checkEnemyEnemyCollision(const Enemy& enemy, const Player& player)
{
	if (checkCollision(enemy))
	{
		float enemy1DistToPlayer = glm::length(m_pos - player.getPos());
		float enemy2DistToPlayer = glm::length(enemy.m_pos - player.getPos());
		float dot = glm::dot(glm::normalize(m_velocity), glm::normalize(enemy.m_velocity));
	}
}

bool Enemy::operator==(const Enemy& enemy)
{
	if (this == &enemy)
	{
		return true;
	}
	return false;
}

bool Enemy::operator!=(const Enemy& enemy)
{
	return !(*this == enemy);
}
