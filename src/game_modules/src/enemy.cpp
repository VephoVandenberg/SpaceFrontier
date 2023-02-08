#include "../include/enemy.h"

using namespace GAME_NAMESPACE::GameModule;

Enemy::Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
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

void Enemy::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader, m_texture);
}
