#include "../include/game_object.h"

using namespace GAME_NAMESPACE::GameModule;

GameObj::GameObj(glm::vec3 scale, glm::vec3 pos, float angle) 
	: m_pos(pos)
	, m_scale(scale)
	, m_angle(angle)
{

}

GameObj::GameObj(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: m_pos(pos)
	, m_scale(scale)
	, m_texture(texture)
{

}

void GameObj::draw(System::Shader& shader, System::Renderer& renderer, bool hasTexture)
{
	if (hasTexture)
	{
		renderer.draw(m_angle, m_scale, m_pos, shader, m_texture);
	}
	else
	{
		renderer.draw(m_angle, m_scale, m_pos, shader);
	}
}

void GameObj::update(glm::vec3 newPos, float newAngle)
{
	m_pos = newPos;
	m_angle = newAngle;
}

bool GameObj::checkCollision(const GameObj& obj) const
{
	bool collisionX = m_pos.x + m_scale.x >= obj.m_pos.x && obj.m_pos.x + obj.m_scale.x >= m_pos.x;
	bool collisionY = m_pos.y + m_scale.y >= obj.m_pos.y && obj.m_pos.y + obj.m_scale.y >= m_pos.y;

	return collisionX && collisionY;
}
