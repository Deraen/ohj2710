#include "SDL.h"
#include "SDL_log.h"

#include "Screen.hpp"
#include "Game.hpp"
#include "interfaces/Drawable.hpp"
#include "interfaces/Touchable.hpp"
#include "objects/Sprite.hpp"
#include "DebugDraw.hpp"

Screen::Screen():
	window_(NULL),
	pixelsPerMeter_(0),
	renderer_(NULL),
	surface_(NULL),
	w_(0),
	h_(0),
	debug_(true),
	debugger_(NULL)
{
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
	window_ = SDL_CreateWindow("PELI",
	                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                           1280, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	// Get the first available Hardware-accelerated renderer for this window.
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	resized();

	debugger_ = new DebugDraw();
	debugger_->SetFlags(b2Draw::e_shapeBit
	                    | b2Draw::e_aabbBit
	                    | b2Draw::e_jointBit
	                    | b2Draw::e_centerOfMassBit);
	Game::instance().world()->SetDebugDraw(debugger_);
}

void Screen::destroy()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Screen::draw()
{
	// Black base color.
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	// Clear the entire screen to the Renderer's base colour.
	SDL_RenderClear(renderer_);

	b2Body* body = Game::instance().world()->GetBodyList();
	while (body != NULL) {
		Drawable* obj = dynamic_cast<Drawable*>((Object*)body->GetUserData());
		if (obj != NULL) {
			obj->sprite()->draw(body);
		}

		body = body->GetNext();
	}

	if (debug_)
	{
		Game::instance().world()->DrawDebugData();
	}

	// Flip the shown and hidden buffers to refresh the screen.
	SDL_RenderPresent(renderer_);
}

bool Screen::Hit::ReportFixture(b2Fixture *fixture)
{
	// SDL_Log("Fixture touched");
	b2Body* body = fixture->GetBody();
	Touchable* touchable = dynamic_cast<Touchable*>((Object*)body->GetUserData());
	if (touchable != NULL && fixture->TestPoint(p_)) {
		touchable->touched(p_);
	}
	return true;
}

void Screen::processInput()
{
	static SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (
			(event.type == SDL_QUIT)
		 || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_AC_BACK)
			)
		{
			Game::instance().stop();
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				Screen::instance().resized();
			}
		}
		else if (
				(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			 || (event.type == SDL_FINGERDOWN)
				)
		{
			b2Vec2 p;

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				p.Set(event.button.x, event.button.y);
			}
			else if (event.type == SDL_FINGERDOWN)
			{
				p.Set(event.tfinger.x, event.tfinger.y);
				SDL_Log("Touch point (%f, %f)", p.x, p.y);

				// Quess: Touch points are represented with values from
				// 0 to 32768
				p.x = (p.x * DEF_SCREEN_WIDTH) / 32768;
				p.y = (p.y * DEF_SCREEN_HEIGHT) / 32768;
			}

			p.x -= w_ / 2;
			p.y -= h_ / 2;

			p = toMeters(p);

			SDL_Log("Mouse/Touch down, (%f, %f)", p.x, p.y);

			Hit hit;
			hit.setPoint(p);

			b2AABB aabb;
			aabb.lowerBound = b2Vec2(p);
			aabb.upperBound = b2Vec2(p);
			Game::instance().world()->QueryAABB(&hit, aabb);
		}
		else
		{
			// SDL_Log("%i", event.type);
			if (event.type == SDL_KEYDOWN) {
				// SDL_Log("key %s", SDL_GetScancodeName(event.key.keysym.scancode));
			}
		}
	}
}

void Screen::resized()
{
	SDL_GetWindowSize(window_, &w_, &h_);

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = w_;
	rect.h = h_;

	// Compute new pixels per meter
	// Planet is 4 meters and should be 128px on 800px wide screen.
	pixelsPerMeter_ = 128.0 * w_ / (DEF_SCREEN_WIDTH * 4.0);

	SDL_Log("Screen resolution %ix%i, pixels per meter %i", w_, h_, pixelsPerMeter_);

	// Render viewport needs to be fixed after resize or it will be
	// messed up after window shrinking.
	SDL_RenderSetViewport(renderer_, &rect);
}

b2Vec2 Screen::toPixels(const b2Vec2 &coord, bool center) const
{
	b2Vec2 copy(coord);
	copy *= pixelsPerMeter_;
	if (center)
	{
		copy.x += w_ / 2;
		copy.y += h_ / 2;
	}
	return copy;
}

b2Vec2 Screen::toMeters(const b2Vec2 &coord) const
{
	b2Vec2 copy(coord.x / pixelsPerMeter_, coord.y / pixelsPerMeter_);
	return copy;
}
