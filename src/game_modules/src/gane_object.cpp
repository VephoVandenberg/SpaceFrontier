#include "../include/game_object.h"

using namespace GAME_NAMESPACE::GameModule;

GameObj::GameObj(glm::vec3 scale, glm::vec3 pos) 
	: m_pos(pos)
	, m_scale(scale)
{

}

GameObj::GameObj(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: m_pos(pos)
	, m_scale(scale)
	, m_texture(texture)
{

}

void GameObj::draw(System::Shader& shader, System::Renderer& renderer)
{
	renderer.draw(m_angle, m_scale, m_pos, shader, m_texture);
}

void GameObj::update(glm::vec3 newPos, float newAngle)
{
	m_pos = newPos;
	m_angle = newAngle;
}
