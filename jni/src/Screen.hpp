

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "SDL.h"
#include "Box2D/Box2D.h"

#include "Object.hpp"

class DebugDraw;

class Touchable;

class Screen: public b2QueryCallback
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

	void processInput();
	bool ReportFixture(b2Fixture* fixture); // b2QueryCallback

	b2Vec2 TouchPosition(const SDL_Event& event);

	// For conversions between screen and Box2D coordinates.
	unsigned int pixelsPerMeter() const { return pixelsPerMeter_; }
	b2Vec2 toPixels(const b2Vec2& coord, bool center = false) const;
	b2Vec2 toMeters(const b2Vec2& coord) const;

	static const int DEF_SCREEN_WIDTH = 800;
	static const int DEF_SCREEN_HEIGHT = 480;

private:
	// Window and Renderer.
	SDL_Window* window_;

	SDL_Renderer* renderer_;
	SDL_Surface* surface_;

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
};

#endif /* SCREEN_HPP_ */
