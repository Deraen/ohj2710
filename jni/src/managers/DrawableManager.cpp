#include <algorithm>

#include "SDL.h"
#include "SDL_log.h"

#include "DrawableManager.hpp"

void DrawableManager::drawAll()
{
	// Clear the entire screen to the Renderer's base colour.
	SDL_RenderClear(renderer_);

	withObjects([](Drawable* obj)
	{
		obj->draw();
	});

	// Flip the shown and hidden buffers to refresh the screen.
	SDL_RenderPresent(renderer_);
}


void DrawableManager::init()
{
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // | SDL_INIT_AUDIO
	{
		return;
	}

	// Debug SDL, on Android messages go to log, on Linux to stderr.
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

	// Create the application window. The size chosen is logical, not the exact
	// number of pixels of the window (mobiles will override it).
	window_ = SDL_CreateWindow("My SDL 1.3 Test",
	                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                           800, 480, SDL_WINDOW_SHOWN);

	// Get the first available Hardware-accelerated renderer for this window.
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	// Black base color.
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
}

void DrawableManager::destroy()
{
	// Remember to free up all the memory we've used, this ain't no Java!
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

}

SDL_Renderer* DrawableManager::renderer() const
{
	return renderer_;
}
