#include <time.h>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../../include/enemies/enemy.h"
#include "../../include/player.h"

#include "../../../system/include/texture.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_enemyVelocityCoeff = 250.0f;
constexpr float g_attackRange = 500.0f;
constexpr float g_deltaAngle = 180.0f;
constexpr float g_PI = 3.14159265359f;
constexpr float g_borderAddition = 200.0f;
constexpr glm::vec3 g_projSize = { 2.0f, 15.0f, 0.0f };

Enemy::Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
	, m_health(3)
	, m_timer(0.0f)
	, m_state(EnemyState::Patrolling)
{
	m_angle = (rand() % 360);

	m_orientation.x = glm::sin(glm::radians(m_angle));
	m_orientation.y = -glm::cos(glm::radians(m_angle));

	m_velocity = m_orientation * g_enemyVelocityCoeff;

	m_orientation = glm::normalize(m_orientation);
}

void Enemy::update(float dt, float borderX, float borderY, Player& player, const glm::vec3& cameraPos, const std::vector<Enemy>& enemies)
{
	m_timer += dt;
	// Enemy's behaviour
	switch (m_state)
	{
	case EnemyState::Patrolling:
	{
		glm::vec3 v1 = alignment(enemies);
		glm::vec3 v2 = cohesion(enemies);
		glm::vec3 v3 = separation(enemies);
		glm::vec3 v4 = patrollVector();

		m_velocity = m_velocity + (v1 + v2 + v3 + v4);
		m_velocity = g_enemyVelocityCoeff * glm::normalize(m_velocity);

		// Turn the ship to align orienation vector and velocity
		glm::vec2 normVel = glm::normalize(m_velocity);
		float angle = glm::orientedAngle(normVel, glm::vec2(m_orientation)) * 180 / g_PI;
		if (std::abs(angle) > 0.5f)
		{
			m_angle += (angle > 0) ? -g_deltaAngle * dt : g_deltaAngle * dt;
			m_orientation.x = glm::sin(glm::radians(m_angle));
			m_orientation.y = -glm::cos(glm::radians(m_angle));
			m_orientation = glm::normalize(m_orientation);
		}
		m_pos += m_velocity * dt;


		if (glm::length(m_pos - player.getPos()) < g_attackRange - 100.0f)
		{
			m_shootingTimeGap = rand() % 5 + 3;
			m_timer = 0.0f;
			m_state = EnemyState::Fighting;
		}
		else if (glm::length(m_pos - player.getPos()) < g_attackRange)
		{
			// m_state = EnemyState::Chasing;
		}
	}break;

	case EnemyState::Fighting:
	{
		glm::vec2 distToPlayer = glm::normalize(player.getPos() + player.getScale() / 4.0f - m_pos);
		float angle = glm::orientedAngle(distToPlayer, glm::vec2(m_orientation));

		/*
		glm::vec3 v1 = alignment(enemies);
		glm::vec3 v2 = cohesion(enemies);
		glm::vec3 v3 = separation(enemies);
		if (glm::length(v3) != 0)
		{
			m_velocity += v3;
			m_velocity = g_enemyVelocityCoeff * glm::normalize(m_velocity);
			m_pos += m_velocity * dt;
		}
		*/

		if (std::abs(angle) > 0.0f)
		{
			m_angle += (angle > 0) ? -g_deltaAngle * dt : g_deltaAngle * dt;
			m_orientation.x = glm::sin(glm::radians(m_angle));
			m_orientation.y = -glm::cos(glm::radians(m_angle));
			m_orientation = glm::normalize(m_orientation);
		}

		if (m_timer > m_shootingTimeGap &&
			std::abs(angle) < 10.0f)
		{
			shoot();
			m_timer = 0;
		}

		if (glm::length(m_pos - player.getPos()) > g_attackRange - 100.0f)
		{
			m_state = EnemyState::Patrolling;
		}

	}break;

	case EnemyState::Chasing:
	{

	}break;

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

	// Check if player was hit by projectile
	unsigned int damage = 0;
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

	player.checkProjEnemyCoollision(*this);
	player.takeDamage(damage);
}

glm::vec3 Enemy::alignment(const std::vector<Enemy>& enemies) const
{
	glm::vec3 averageVel = glm::vec3(0.0f);
	unsigned int total = 0;
	for (auto& enemy : enemies)
	{
		if (*this != enemy &&
			enemy.m_state != EnemyState::Fighting &&
			glm::length(m_pos - enemy.m_pos) < 120.0f)
		{
			averageVel += enemy.m_velocity;
			total++;
		}
	}

	if (total > 0)
	{
		averageVel /= total;
		averageVel -= m_velocity;
	}

	return averageVel;
}

glm::vec3 Enemy::separation(const std::vector<Enemy>& enemies) const
{
	glm::vec3 separation = glm::vec3(0.0f);
	unsigned int total = 0;
	for (auto& enemy : enemies)
	{
		if (*this != enemy &&
			glm::length(m_pos - enemy.m_pos) < 90.0f)
		{
			separation += (m_pos - enemy.m_pos);
			total++;
		}
	}

	return separation;
}

glm::vec3 Enemy::cohesion(const std::vector<Enemy>& enemies) const
{
	glm::vec3 averagePos = glm::vec3(0.0f);
	unsigned int total = 0;

	for (auto& enemy : enemies)
	{
		if (*this != enemy &&
			enemy.m_state != EnemyState::Fighting &&
			glm::length(m_pos - enemy.m_pos) < 120.0f)
		{
			averagePos += enemy.m_pos;
			total++;
		}
	}

	if (total > 0)
	{
		averagePos /= total;
		averagePos -= m_pos;
		averagePos /= 100.0f;
	}

	return averagePos;
}

glm::vec3 Enemy::patrollVector() const
{
	float angle = m_angle + 10.0f;
	glm::vec3 patrollVector = glm::vec3(0.0f);

	patrollVector.x = glm::sin(glm::radians(angle));
	patrollVector.y = -glm::cos(glm::radians(angle));

	return patrollVector;
}

void Enemy::updatePosition(float dt, bool isMovingForward)
{
	m_pos += (isMovingForward) ? m_velocity * dt : -m_velocity * dt;
	m_velocity *= 0.995f;
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

bool Enemy::operator==(const Enemy& enemy) const
{
	if (this == &enemy)
	{
		return true;
	}
	return false;
}

bool Enemy::operator!=(const Enemy& enemy) const
{
	return !(*this == enemy);
}
