#include "../../include/space_objects/meteorite.h"

using namespace GAME_NAMESPACE::GameModule;

Meteorite::Meteorite(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: SpaceObj(pos, scale, texture)
{

}