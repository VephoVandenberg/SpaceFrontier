#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

/*
* TODO List
* Agenda:
* - 
* Later:
* - fix the collision between projectiles and enemies
* - adapt dt in movement for the player
* - change the dealocation of the projectiles when it is out of the borders
* - 
*/

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
