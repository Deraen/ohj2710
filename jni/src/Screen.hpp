#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "SDL.h"

class Screen
{
public:
	Screen()
	{
	}

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

	void drawAll();

	bool processInput();

	inline SDL_Renderer* renderer() const { return renderer_; }

	void resized();

	template<typename E>
	void toScreenCoordinates(E& x, E& y) const
	{
		// XXX: Round?
		x = x * scale_;
		y = y * scale_;
	}

	// b2Vec2 toScreenCoordinates(const b2Vec2& coord) const;
	SDL_Rect toScreenCoordinates(const SDL_Rect& rect) const;

	static const int DEF_SCREEN_WIDTH = 800;
	static const int DEF_SCREEN_HEIGHT = 480;

private:
	// Window and Renderer.
	SDL_Window* window_;
	float scale_;

	SDL_Renderer* renderer_;
	SDL_Surface* surface_;

	int w_;
	int h_;
};

#endif /* SCREEN_HPP_ */
