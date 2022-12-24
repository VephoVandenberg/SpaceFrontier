#include "src/include/game.h"

using namespace GAME_NAMESPACE;

int main(int argc, char** argv)
{
	std::unique_ptr<Game> app = std::make_unique<Game>();
	app->run();
	return 0;
}
