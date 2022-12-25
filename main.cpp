#include "src/game_base/include/game.h"

using App = GAME_NAMESPACE::Game;

int main(int argc, char** argv)
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();

	return 0;
}
