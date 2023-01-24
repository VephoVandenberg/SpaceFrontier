#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

Player::Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: GameObj(scale, pos, texture)
{
	init();
}

void Player::init()
{
	m_acceleration = 0.6f;
}

void Player::update(float dt, float angle, MoveDir dir)
{
	m_angle += angle * 0.5f;
	
	if (dir == MoveDir::Up)
	{
		m_velocity.x = glm::sin(m_angle) * m_acceleration;
		m_velocity.y = -glm::cos(m_angle) * m_acceleration;
	}
	else if (dir == MoveDir::Bottom)
	{
		m_velocity.x = -glm::sin(m_angle) * m_acceleration;
		m_velocity.y = glm::cos(m_angle) * m_acceleration;
	}
	m_pos += m_velocity;
	m_velocity *= 0.995f;
}
