#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr unsigned int g_fullMag = 64;
constexpr glm::vec3 g_projSize = { 2.0f, 15.0f, 0.0f };

Player::Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: GameObj(scale, pos, texture)
	, m_acceleration(0.6f)
{}

// NOTE: Adapt dt to the movement
void Player::update(float dt, float angle, float borderX, float borderY, MoveDir dir)
{
	// Position update
	m_angle += angle * 0.5f;

	if (dir == MoveDir::Up)
	{
		m_velocity.x =  glm::sin(m_angle) * m_acceleration;
		m_velocity.y = -glm::cos(m_angle) * m_acceleration;
	}
	else if (dir == MoveDir::Bottom)
	{
		m_velocity.x = -glm::sin(m_angle) * m_acceleration;
		m_velocity.y =  glm::cos(m_angle) * m_acceleration;
	}
	m_pos += m_velocity;
	m_velocity *= 0.995f;

	// Projectile update
	for (auto& proj : m_projectiles)
	{
		proj.update();
	}

	if (!m_projectiles.empty() && m_projectiles.back().isOut(borderX, borderY))
	{
		m_projectiles.pop_front();
	}

}

void Player::shoot()
{
	glm::vec3 projPos = glm::vec3(m_pos.x + m_scale.x / 2.0f, m_pos.y + m_scale.y / 3.0f, 0.0f);
	m_projectiles.push_back(Projectile(projPos, g_projSize, m_color, m_velocity, m_angle));
}

void Player::drawProjectiles(System::Shader& shader, System::Renderer& renderer)
{
	for (auto& proj : m_projectiles)
	{
		proj.draw(shader, renderer, false);
	}
}

void Player::checkProjEnemyCoollision(Enemy& enemy)
{
	// NOTE: fix the collision later
	if (!m_projectiles.empty())
	{
		for (auto it = m_projectiles.begin(); it != m_projectiles.end(); it++)
		{
			if (it->checkCollision(enemy))
			{
				m_projectiles.erase(it);
				break;
			}
		}
	}
}
