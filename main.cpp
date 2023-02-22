#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* - menu scene has to be made
* - switching between menu and level1
* - a good random number genreator is needed, or at least read about it
* Later:
* - stationary objects like asteroids must be added, as well as dynamic meteors
* - how the map should be drawn, think about it?
* - draw textures
*/

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
