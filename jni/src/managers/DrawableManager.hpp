/*
 * DrawableManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef DRAWABLEMANAGER_HPP_
#define DRAWABLEMANAGER_HPP_

#include "SDL.h"

#include "Manager.hpp"
#include "objects/Drawable.hpp"

class DrawableManager: public Manager<Drawable>
{
public:
	DrawableManager():
		Manager(100)
	{
	}

	virtual ~DrawableManager()
	{
	}

	static DrawableManager& instance()
	{
		static DrawableManager instance_;
		return instance_;
	}

	void init();

	void destroy();

	void drawAll();

	SDL_Renderer* renderer() const;

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
	int w_;
	int h_;
	float scale_;

	SDL_Renderer* renderer_;
	SDL_Surface* surface_;
};

#endif /* DRAWABLEMANAGER_HPP_ */
