/*
 * DrawableManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef DRAWABLEMANAGER_HPP_
#define DRAWABLEMANAGER_HPP_

#include "SDL.h"

#include "../Manager.hpp"
#include "../objects/Drawable.hpp"

class DrawableManager: public Manager<Drawable> {
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

private:
	/*
	 * Linked list?
	 */
	std::vector<Drawable*> drawables_;

	// Window and Renderer.
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	SDL_Surface* surface_;
};

#endif /* DRAWABLEMANAGER_HPP_ */
