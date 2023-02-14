#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* - primitive ai must be applied
* Later:
* - think about the states and scenes, and read about them if necessary
* - draw textures
*/

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
