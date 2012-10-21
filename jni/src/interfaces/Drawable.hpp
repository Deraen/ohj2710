/*
 * Drawable.hpp
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>

#include "SDL.h"
#include "Box2D/Box2D.h"

class Drawable
{
public:
	Drawable() {};
	virtual ~Drawable() {};

	/*
	 * Returns name of the texture that shold represent this object.
	 */
	virtual unsigned int sprite() const = 0;

	/*
	 * In what angle should the texture be drawn.
	 */
	virtual float angle() const = 0;

	/*
	 * Position of object.
	 * XXX: On what coordinate system?
	 */
	virtual b2Vec2 pos() const = 0;

	/*
	 * Dimension of sprite on screen.
	 */
	virtual b2Vec2 dimensions() const = 0;
private:
};

#endif /* Drawable_HPP_ */
