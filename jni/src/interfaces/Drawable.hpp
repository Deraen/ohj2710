/*
 * Drawable.hpp
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>

#include "SDL.h"
#include "Box2D/Box2D.h"

class Sprite;

class Drawable
{
public:
	Drawable() {};
	virtual ~Drawable() {};

	/*
	 * Returns name of the texture that shold represent this object.
	 */
	virtual Sprite* sprite() const = 0;

	/*
	 * Dimension of sprite on screen.
	 */
	virtual b2Vec2 dimensions() const = 0;
private:
};

#endif /* Drawable_HPP_ */
