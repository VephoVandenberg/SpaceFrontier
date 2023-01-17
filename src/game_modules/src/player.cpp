#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

Player::Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: GameObj(scale, pos, texture)
{
	init();
}

void Player::init()
{

}

void Player::update(float dt, float angle, MoveDir dir)
{
	m_angle += angle * 0.5f;
	
	if (dir == MoveDir::Up)
	{
		m_velocity.x = glm::sin(m_angle) * 0.3f;
		m_velocity.y = -glm::cos(m_angle) * 0.3f;

	}
	m_pos += m_velocity;
	m_velocity *= 0.995f;
}
