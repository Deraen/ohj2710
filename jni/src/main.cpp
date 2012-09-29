#include "SDL.h"

#include "managers/PlayerManager.hpp"
#include "managers/DrawableManager.hpp"

int main(int argc, char* argv[])
{
	// Window and Renderer.
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 1;
	}

	// Create the application window. The size chosen is logical, not the exact
	// number of pixels of the window (mobiles will override it).
	window = SDL_CreateWindow("My SDL 1.3 Test",
	                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                          640, 480, SDL_WINDOW_SHOWN);

	// Get the first available Hardware-accelerated renderer for this window.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Black base color.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Init objects.
	unsigned int player1 = PlayerManager::instance().newObject();

	// Execute the main loop.
	bool running = true;
	while(running)
	{
		// Clear the entire screen to the Renderer's base colour.
		SDL_RenderClear(renderer);

		DrawableManager::instance().drawAll();

		// Flip the shown and hidden buffers to refresh the screen.
		SDL_RenderPresent(renderer);

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

	// Remember to free up all the memory we've used, this ain't no Java!
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// all clear, return EXIT_SUCCESS
	return 0;
}
