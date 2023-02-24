#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* Later:
* - how to make enemies know about each other's position and not to overlap with each other?
* - how the map should be drawn, think about it?
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
