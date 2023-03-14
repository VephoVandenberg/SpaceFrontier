#include "../../system/include/renderer.h"
#include "../../system/include/shader.h"

#include "../include/game_object.h"

using namespace GAME_NAMESPACE::GameModule;

GameObj::GameObj(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, float angle)
	: m_pos(pos)
	, m_scale(scale)
	, m_color(color)
	, m_angle(angle)
{}

void GameObj::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, m_color, cameraPos, shader);
}

bool GameObj::checkCollision(const GameObj& obj) const
{
	bool collisionX = 
		m_pos.x + m_scale.x >= obj.m_pos.x && 
		obj.m_pos.x + obj.m_scale.x>= m_pos.x;
	bool collisionY = 
		m_pos.y + m_scale.y >= obj.m_pos.y &&
		obj.m_pos.y + obj.m_scale.y >= m_pos.y;

	return collisionX && collisionY;
}

