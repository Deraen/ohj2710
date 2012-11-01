
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
#include "Assets.hpp"

/*
 * A planet is a player.
 */
class Planet: public Object, public Drawable, public Touchable
{
public:
	Planet();
	virtual ~Planet();

	inline Sprite* sprite() const { return type_.sprite; }
	inline b2Vec2 dimensions() const { return type_.meters; }

	void touched(const b2Vec2& touchPosition);

	static const float RADIUS;

private:
	b2Body* body_;
	Assets::Type type_;
};

#endif /* PLANET_H_ */
