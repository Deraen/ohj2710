#include <cstdlib>

#include "SDL.h"

#include "Game.hpp"
#include "Screen.hpp"
#include "Assets.hpp"

int main(int argc, char* argv[])
{
	// Load screen first so Sprites can create textures.
	Screen::instance().init();
	// Load assets before creating world so objects can find their
	// sprites when initialized.
	Assets::instance().init();
	Game::instance().init();

	// Execute the main loop.
	Game::instance().loop();

	Screen::instance().destroy();

	// all clear, return EXIT_SUCCESS
	return 0;
}
