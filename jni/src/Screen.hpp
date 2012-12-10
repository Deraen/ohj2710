

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <cstdint>
#include "SDL.h"
#include "Box2D/Box2D.h"
#include "SDL_ttf.h"

#include "Object.hpp"

class DebugDraw;

class Touchable;

class UI;

class Screen//: public b2QueryCallback
{
public:
	Screen();

	virtual ~Screen();

	static Screen& instance()
	{
		static Screen instance_;
		return instance_;
	}

	void init();
	void destroy();
	void draw();
	void resized();

	// For sprites
	inline SDL_Renderer* renderer() const { return renderer_; }
	inline TTF_Font* font() const { return font_; }

	void processInput();
	// bool ReportFixture(b2Fixture* fixture); // b2QueryCallback

	std::pair<unsigned int, unsigned int> TouchPosition(const SDL_Event& event);
	b2Vec2 TouchPositionMeters(const SDL_Event& event);

	// For conversions between screen and Box2D coordinates.
	unsigned int pixelsPerMeter() const { return pixelsPerMeter_; }
	unsigned int ResX() const { return w_; }
	unsigned int ResY() const { return h_; }
	b2Vec2 toPixels(const b2Vec2& coord, bool center = false) const;
	b2Vec2 toMeters(const b2Vec2& coord) const;

	inline bool Debug() { return debug_; }
	inline void ToggleDebug() { debug_ = !debug_; }

	static const int DEF_SCREEN_WIDTH = 800;
	static const int DEF_SCREEN_HEIGHT = 480;

	static SDL_Surface* CreateSurface(int width, int height, int depth);
	static SDL_Surface* CreateSurfaceFrom(void* data, int width, int height, int depth, int pitch);

private:
	// Window and Renderer.
	SDL_Window* window_;

	SDL_Renderer* renderer_;
	SDL_Surface* surface_;
	TTF_Font* font_;

	// Window size
	int w_;
	int h_;

	// From box2d coordinates to screen coordinates
	unsigned int pixelsPerMeter_;

	// Debug
	bool debug_;
	DebugDraw* debugger_;

	// Input
	b2Vec2 touchPoint_;
	Touchable* touchObject_;

	UI* ui_;

	static Uint32 RMASK;
	static Uint32 GMASK;
	static Uint32 BMASK;
	static Uint32 AMASK;
};

#endif /* SCREEN_HPP_ */
