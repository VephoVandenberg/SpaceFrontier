#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* - how to make enemies know about each other's position and not to overlap with each other?
* Later:
* - how the map should be drawn, think about it?
* - how the groups must work, or should I actually have them in the game?
* - simple init of space objects
* - stationary objects like asteroids must be added, as well as dynamic meteors
* - learn about rng
* - draw textures
*/

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
