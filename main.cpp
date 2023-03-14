#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* - stationary objects like asteroids must be added, as well as dynamic meteors
* Later:
* - how the map should be drawn, think about it?
* - simple init of space objects
* - think about adding the particle system
* - learn about rng
* - draw textures
* - restrict the group where to fly, enemies fly away too far
* Super later
* - Haiving acceptable behaviour but it still can be improved
*/

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
