#include "SDL.h"

#include "managers/PlayerManager.hpp"
#include "managers/DrawableManager.hpp"

int main(int argc, char* argv[])
{
	DrawableManager::instance().init();

	// Init objects.
	unsigned int player1 = PlayerManager::instance().newObject();
	Player* obj = PlayerManager::instance().getObject(player1);
	obj->initialize("Pelaaja 1");

	// Execute the main loop.
	bool running = true;
	while(running)
	{
		DrawableManager::instance().drawAll();

		// Give other applications some time to execute.
		SDL_Delay(50);

		// Check for input events and exit if the window is closed (ex: pressing
		// the cross, closed by the OS)
		static SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}

	DrawableManager::instance().destroy();

	// all clear, return EXIT_SUCCESS
	return 0;
}
