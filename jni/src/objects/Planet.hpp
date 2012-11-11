
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

	void Draw(b2Body* body) const;
	inline Sprite* GetSprite() const { return type_.sprite; }
	inline b2Vec2 GetDimensions() const { return type_.meters; }

	void TouchStart();
	void TouchMovement(const b2Vec2& p);
	void TouchEnd();

	static const float RADIUS;
private:
	b2Body* body_;
	Assets::Type type_;

	bool touched_;
	b2Vec2 touchPosition_;
};

#endif /* PLANET_H_ */
