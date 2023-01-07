#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

Player::Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture)
	: GameObj(scale, pos, texture)
{
	init();
}

void Player::init()
{

}