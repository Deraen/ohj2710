#include <algorithm>

#include "SDL.h"
#include "SDL_log.h"

#include "Screen.hpp"
#include "Manager.hpp"
#include "interfaces/Drawable.hpp"
#include "objects/Sprite.hpp"

void Screen::drawAll()
{
	// Clear the entire screen to the Renderer's base colour.
	SDL_RenderClear(renderer_);

	Manager::instance().withObjects<Drawable>([](Drawable* obj)
	{
		Manager::instance().withObject<Sprite>(obj->sprite(), [&](Sprite* sprite) {
			sprite->draw(obj);
		});
	});

	// Flip the shown and hidden buffers to refresh the screen.
	SDL_RenderPresent(renderer_);
}


void Screen::init()
{
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // | SDL_INIT_AUDIO
	{
		return;
	}

	// Debug SDL, on Android messages go to log, on Linux to stderr.
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

	/*
	 * On android, this resolution is ignored and devices screen resolution
	 * is used instead.
	 * Windows are never resizable on Android.
	 */
	window_ = SDL_CreateWindow("My SDL 1.3 Test",
	                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                           1280, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	// Get the first available Hardware-accelerated renderer for this window.
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	resized();

	// Black base color.
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

	// XXX:
	unsigned int earth = Manager::instance().newObject<Sprite>();
	Manager::instance().withObject<Sprite>(earth, [](Sprite* obj) {
		obj->initialize();
	});
	unsigned int asteroid = Manager::instance().newObject<Sprite>();
	Manager::instance().withObject<Sprite>(asteroid, [](Sprite* obj) {
		obj->initialize();
	});
}

void Screen::destroy()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Screen::resized()
{
	SDL_GetWindowSize(window_, &w_, &h_);
	scale_ = static_cast<float>(w_) / DEF_SCREEN_WIDTH;

	SDL_Log("Screen resolution %ix%i, scale %f", w_, h_, scale_);

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = w_;
	rect.h = h_;

	// Render viewport needs to be fixed after resize or it will be
	// messed up after window shrinking.
	SDL_RenderSetViewport(renderer_, &rect);
}

// b2Vec2 Screen::toScreenCoordinates(const b2Vec2 &coord) const
// {
// 	b2Vec2 copy(coord);
// 	toScreenCoordinates(copy.x, copy.y);
// 	return copy;
// }

SDL_Rect Screen::toScreenCoordinates(const SDL_Rect &rect) const
{
	SDL_Rect copy(rect);
	toScreenCoordinates(copy.x, copy.y);
	toScreenCoordinates(copy.w, copy.h);

	// Move to window coordinate system. = 0,0 window topleft.
	// For drawing we need topleft coordinate instead of obj center coordinates.
	copy.x += w_ / 2 - copy.w / 2;
	copy.y += h_ / 2 - copy.h / 2;
	return copy;
}
