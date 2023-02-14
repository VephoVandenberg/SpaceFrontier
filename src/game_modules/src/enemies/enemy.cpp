#include "../../include/enemies/enemy.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_enemyVelocityCoeff = 100.0f;
constexpr float g_attackRange = 600.0f;
constexpr float g_deltaAngle = 1.0f;

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

void Enemy::update(float dt, const GameObj& playerObj)
{
	m_timer += dt;

	switch (m_state)
	{

	case EnemyState::Idle:
		if (glm::length(playerObj.getPos() - m_pos) <= g_attackRange)
		{
			m_state = EnemyState::Atacking;
			m_timer = 0.0f;
			break;
		}

		if (m_timer >= 3.0f)
		{
			m_state = EnemyState::Patrolling;
			m_timer = 0.0f;

			m_velocity.x = glm::sin(m_angle) * g_enemyVelocityCoeff;
			m_velocity.y = (m_velocity.y < 0.0f) ? glm::cos(m_angle) * g_enemyVelocityCoeff : -glm::cos(m_angle) * g_enemyVelocityCoeff;
		}
		break;

	case EnemyState::Patrolling:
		
		if (m_timer >= 3.0f)
		{
			m_state = EnemyState::Idle;
			m_timer = 0.0f;
		}

		m_pos += m_velocity * dt;
		break;

	case EnemyState::Atacking:
		if (glm::dot(
			glm::normalize(m_velocity), 
			glm::normalize(playerObj.getPos() - m_pos)) < 1.0f)
		{
			
			float dot = glm::dot(
				glm::normalize(m_velocity),
				glm::normalize(playerObj.getPos() - m_pos));
			
			m_angle += g_deltaAngle * dt;
		}

		if (glm::length(playerObj.getPos() - m_pos) >= g_attackRange + 200)
		{
			m_state = EnemyState::Idle;
			break;
		}

		break;

	case EnemyState::Fleeing:
		break;

	}
}

void Enemy::shoot()
{

}

void Enemy::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader, m_texture);
}