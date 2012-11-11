

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "SDL.h"
#include "Box2D/Box2D.h"

#include "Object.hpp"

class DebugDraw;

class Screen
{
public:
	Screen();

	virtual ~Screen()
	{
	}

	static Screen& instance()
	{
		static Screen instance_;
		return instance_;
	}

	void init();

	void destroy();

	void draw();

	void processInput();

	// For sprites
	inline SDL_Renderer* renderer() const { return renderer_; }

	void resized();

	unsigned int pixelsPerMeter() const { return pixelsPerMeter_; }

	// Meters -> Pixels
	b2Vec2 toPixels(const b2Vec2& coord, bool center = false) const;

	// Pixels -> Meters
	b2Vec2 toMeters(const b2Vec2& coord) const;

	static const int DEF_SCREEN_WIDTH = 800;
	static const int DEF_SCREEN_HEIGHT = 480;

	class Hit: public b2QueryCallback {
	public:
		Hit() {};
		virtual ~Hit() {};

		inline void setPoint(const b2Vec2 p) { p_ = p; }
		bool ReportFixture(b2Fixture* fixture);
	private:
		b2Vec2 p_;
	};

private:
	// Window and Renderer.
	SDL_Window* window_;

	// From box2d coordinates to screen coordinates
	unsigned int pixelsPerMeter_;

	SDL_Renderer* renderer_;
	SDL_Surface* surface_;

	int w_;
	int h_;

	bool debug_;
	DebugDraw* debugger_;
};

#endif /* SCREEN_HPP_ */
