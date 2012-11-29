/*
 * Drawable.hpp
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "SDL.h"
#include "Box2D/Box2D.h"

class Sprite;

class Drawable
{
public:
	Drawable() {};
	virtual ~Drawable() {};

	virtual void Draw(b2Body* body) const;

	/*
	 * Returns name of the texture that shold represent this object.
	 */
	virtual Sprite* GetSprite() const = 0;

	/*
	 * Dimension of sprite on screen.
	 */
	virtual b2Vec2 GetDimensions() const = 0;
private:
};

#endif /* Drawable_HPP_ */
