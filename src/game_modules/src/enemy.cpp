#include "../include/enemy.h"

using namespace GAME_NAMESPACE::GameModule;

Enemy::Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(scale, pos, texture)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_health(3)
{

}

void Enemy::update(float dt)
{

}

void Enemy::shoot()
{

}

void Enemy::takeDamage()
{
	m_health--;
}

bool Enemy::isAlive() const
{
	return m_health <= 0;
}
