/*
 * Drawable.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "SDL.h"

#include "Object.hpp"

class Drawable: public Object
{
public:
	enum DrawableType {
		CIRCLE,
		TRIANGLE,
		SPRITE,
	};

	Drawable();
	virtual ~Drawable();

	void reset_inner();

	void initialize(DrawableType type, int x, int y, unsigned int w, unsigned int h);

	void circle(float r);

	void draw() const;
private:
	DrawableType type_;

	float r_;

	SDL_Surface* surface_;
	SDL_Texture* texture_;

	/*
	 * Size of texture.
	 */
	SDL_Rect src_;

	/*
	 * Target rectangle on screen.
	 */
	SDL_Rect dst_;
};

#endif /* Drawable_HPP_ */
