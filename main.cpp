#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* - change a bit place where the projectiles should be dealocated
* - adapt movement for the enemies
* Later:
* - think about the states and scenes, and read about them if necessary
* - read about the AI in games
*/

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
