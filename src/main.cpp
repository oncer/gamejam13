#include "Globals.h"
#include "Game.h"

Game* g_game;

int main(int argc, char** argv)
{
	srand(time(0));
 	g_game = new Game();

	try {
		g_game->run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	delete g_game;
	return 0;
}
