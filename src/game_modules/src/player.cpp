#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr unsigned int g_fullMag = 64;
constexpr glm::vec3 g_projSize = { 5.0f, 10.0f, 0.0f };

Player::Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: GameObj(scale, pos, texture)
{
	init();
}

void Player::init()
{
	m_acceleration = 0.6f;
	m_projectiles.reserve(g_fullMag);
}

void Player::update(float dt, float angle, MoveDir dir)
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
 		proj.update(dt);
	}
}

void Player::shoot()
{
	m_projectiles.emplace_back(Projectile(m_pos, g_projSize, m_color, m_velocity, m_angle));
}

void Player::drawProjectiles(System::Shader& shader, System::Renderer& renderer)
{
	for (auto& proj : m_projectiles)
	{
		proj.draw(shader, renderer, false);
	}
}
