#include "../../include/space_objects/space_object.h"

using namespace GAME_NAMESPACE::GameModule;

SpaceObj::SpaceObj(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
{}

void SpaceObj::update(float dt, float borderX, float borderY, Player& player, const glm::vec3& cameraPos, const std::vector<Enemy>& enemies)
{

}

void SpaceObj::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{

}
