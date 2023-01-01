#include "../include/game_object.h"

using namespace GAME_NAMESPACE::GameModule;

GameObj::GameObj(glm::vec3 scale) 
	: m_scale(scale)
{

}

GameObj::GameObj(glm::vec3 scale, System::Texture& texture)
	: m_scale(scale)
	, m_texture(texture)
{

}

void GameObj::draw(System::Shader& shader, System::Renderer& renderer, glm::vec3 pos, glm::vec3 rotation)
{
	renderer.draw(m_scale, pos, shader, m_texture);
}
