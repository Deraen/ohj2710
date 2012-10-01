#include <cstdlib>

#include "SDL.h"

#include "managers/PlayerManager.hpp"
#include "managers/DrawableManager.hpp"
#include "managers/AsteroidManager.hpp"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	DrawableManager::instance().init();

	// Init objects.
	unsigned int player1 = PlayerManager::instance().newObject();
	unsigned int planet1 = 0;
	PlayerManager::instance().withObject(player1, [&](Player* obj)
	{
		obj->initialize("Pelaaja 1");
		planet1 = obj->getPlanet();
	});

	for (unsigned int i = 0; i < 8; ++i)
	{
		unsigned int asteroid = AsteroidManager::instance().newObject();
		AsteroidManager::instance().withObject(asteroid, [&](Asteroid* obj)
		{
			obj->initialize(planet1);
		});
	}

	// Execute the main loop.
	bool running = true;
	while(running)
	{
		DrawableManager::instance().drawAll();

		AsteroidManager::instance().withObjects([](Asteroid* obj)
		{
			obj->move();
		});

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
