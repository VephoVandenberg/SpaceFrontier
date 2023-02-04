#include "../include/enemy.h"

using namespace GAME_NAMESPACE::GameModule;

Enemy::Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale, texture)
	, m_velocity(0.0f, 0.0f, 0.0f)
{

}

void Enemy::update(float dt)
{

}

void Enemy::shoot()
{

}