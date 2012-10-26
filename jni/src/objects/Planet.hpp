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

	void initialize();

	// --- Drawable ---
	unsigned int sprite() const;
	inline float angle() const { return 0.0; }

	// --- Drawable/Toucable ---
	inline b2Vec2 pos() const { return pos_; }
	inline b2Vec2 dimensions() const { return b2Vec2(128, 128); }

	// --- Touchable ---
	inline void SetBody(b2Body* body) { body_ = body; } // XXX: remove this...
	inline b2Body* getBody() const { return body_; }
	void touched(const b2Vec2& touchPosition);

private:
	b2Body* body_;

	b2Vec2 pos_;
};

#endif /* PLANET_H_ */
