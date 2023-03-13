#include "../../include/space_objects/space_object.h"

using namespace GAME_NAMESPACE::GameModule;

SpaceObj::SpaceObj(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
{}

void SpaceObj::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{

}
