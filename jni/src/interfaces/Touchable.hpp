
#ifndef TOUCHABLE_HPP_
#define TOUCHABLE_HPP_

#include <string>

#include "SDL.h"
#include "Box2D/Box2D.h"

class Touchable
{
public:
	Touchable() {};
	virtual ~Touchable() {};

	/*
	 * Callback.
	 */
	virtual void TouchStart() = 0;

	virtual void TouchMovement(const b2Vec2& p) = 0;

	virtual void TouchEnd() = 0;
private:
};

#endif /* TOUCHABLE_HPP_ */
