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

		// Check for input events and exit if the window is closed (ex: pressing
		// the cross, closed by the OS)
		static SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Screen::instance().resized();
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == 1073742094)
				{
					running  = false;
				}
			}
		}

		// Give other applications some time to execute.
		SDL_Delay(20);
	}

	Screen::instance().destroy();

	// all clear, return EXIT_SUCCESS
	return 0;
}
