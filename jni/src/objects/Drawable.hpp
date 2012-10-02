/*
 * Drawable.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "SDL.h"
#include "Box2D/Box2D.h"

#include "Object.hpp"

class Drawable: public Object
{
public:
	Drawable();
	virtual ~Drawable();

	void reset_inner();

	void initialize(const b2Vec2& pos, const b2Vec2& dim);

	void draw() const;

	// fuu
	void updatePos(const b2Vec2& pos);
private:
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
