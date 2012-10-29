/*
 * Planet.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Box2D/Box2D.h"

#include "Object.hpp"
#include "interfaces/Drawable.hpp"
#include "interfaces/Touchable.hpp"

/*
 * A planet is a player.
 */
class Planet: public Object, public Drawable, public Touchable
{
public:
	Planet();
	virtual ~Planet();

	inline Sprite* sprite() const { return sprite_; }
	inline b2Vec2 dimensions() const { return b2Vec2(2 * RADIUS, 2 * RADIUS); }
	void touched(const b2Vec2& touchPosition);

	static const float RADIUS;

private:
	Sprite* sprite_;
	b2Body* body_;
};

#endif /* PLANET_H_ */
