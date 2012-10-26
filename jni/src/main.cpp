#include <cstdlib>

#include "SDL.h"
#include "Manager.hpp"

#include "World.hpp"
#include "Screen.hpp"
#include "Assets.hpp"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	World world;
	Screen::instance().init();
	Assets::instance().init();

	// Execute the main loop.
	bool running = true;
	while(running)
	{
		Screen::instance().drawAll();

		world.Step();

		running = Screen::instance().processInput();

		// Give other applications some time to execute.
		SDL_Delay(20);
	}

	Screen::instance().destroy();

	// all clear, return EXIT_SUCCESS
	return 0;
}
