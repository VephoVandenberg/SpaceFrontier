#include <glm/gtx/vector_angle.hpp>

#include "../../include/enemies/enemy.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_enemyVelocityCoeff = 100.0f;
constexpr float g_attackRange = 200.0f;
constexpr float g_deltaAngle = 1.0f;
constexpr float g_PI = 3.14159265359f;
constexpr float g_borderAddition = 400.0f;
constexpr glm::vec3 g_projSize = { 2.0f, 15.0f, 0.0f };

Enemy::Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
	, m_health(3)
	, m_timer(0.0f)
	, m_state(EnemyState::Idle)
{
	m_velocity.x =  glm::sin(m_angle) * g_enemyVelocityCoeff;
	m_velocity.y = -glm::cos(m_angle) * g_enemyVelocityCoeff;
}

void Enemy::update(float dt, float borderX, float borderY, glm::vec3& cameraPos, const GameObj& playerObj)
{
	m_timer += dt;

	// Enemy's primitive ai
	switch (m_state)
	{

	case EnemyState::Idle:
		idle(playerObj);
		break;

	case EnemyState::Patrolling:
		patroll(dt, playerObj);
		break;

	case EnemyState::Fighting:
		fight(dt, playerObj);
		break;

	case EnemyState::Fleeing:
		flee();
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

void Enemy::idle(const GameObj& playerObj)
{
	if (m_timer >= 3.0f)
	{
		m_state = EnemyState::Patrolling;
		m_timer = 0.0f;

		m_velocity *= -1.0f;
	}

	if (glm::length(playerObj.getPos() - m_pos) <= g_attackRange)
	{
		m_state = EnemyState::Fighting;
		m_shootingTimeGap = static_cast<float>(std::rand() % 3 + 1);
		m_timer = 0.0f;
	}
}

void Enemy::patroll(float dt, const GameObj& playerObj)
{
	if (m_timer >= 3.0f)
	{
		m_state = EnemyState::Idle;
		m_timer = 0.0f;
	}

	if (glm::length(playerObj.getPos() - m_pos) <= g_attackRange)
	{
		m_state = EnemyState::Fighting;
		m_shootingTimeGap = static_cast<float>(std::rand() % 2, 1);
		m_timer = 0.0f;
	}

	m_pos += m_velocity * dt;
}

void Enemy::fight(float dt, const GameObj& playerObj)
{
	glm::vec2 normVel = glm::normalize(m_velocity);
	glm::vec2 normEnemyToPlayer = glm::normalize(playerObj.getPos() + playerObj.getScale() / 4.0f - m_pos);
	float dot = glm::dot(normVel, normEnemyToPlayer);

	if (dot < 0.995f)
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
	else
	{
		if (m_timer >= m_shootingTimeGap)
		{
			shoot();
			m_timer = 0.0f;
		}
	}

	if (glm::length(playerObj.getPos() - m_pos) >= g_attackRange + 200)
	{
		m_state = EnemyState::Idle;
	}
}


void Enemy::flee()
{

}

void Enemy::shoot()
{
	glm::vec3 projPos = glm::vec3(m_pos.x + m_scale.x / 2.0f, m_pos.y + m_scale.y / 3.0f, 0.0f);
	m_projectiles.push_back(Projectile(projPos, g_projSize, m_color, m_velocity, m_angle));
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

int Enemy::checkProjPlayerCoollision(const GameObj& playerObj)
{
	int damage = 0;
	m_projectiles.erase(
		std::remove_if(
			m_projectiles.begin(),
			m_projectiles.end(),
			[&](const Projectile& proj) {
				if (proj.checkCollision(playerObj))
				{
					damage++;
					return true;
				}
				return false;
			}),
		m_projectiles.end());

	return damage;
}
