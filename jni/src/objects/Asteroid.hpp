/*
 * Asteroid.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Box2D/Box2D.h"
#include "Object.hpp"
#include "interfaces/Drawable.hpp"
#include "Assets.hpp"

class Asteroid: public Object, public Drawable
{
public:
	Asteroid(b2Body* planet);
	virtual ~Asteroid();

	// Own functions
	/*
	 * XXX: Fuu.
	 */
	void move();

	inline b2Body* getBody() const { return body_; }

	// --- Drawable ---
	inline Sprite* sprite() const { return type_.sprite; }
	inline b2Vec2 dimensions() const { return type_.meters; }

private:
	Assets::Type type_;
	b2Body* body_;
};

#endif /* ASTEROID_H_ */
