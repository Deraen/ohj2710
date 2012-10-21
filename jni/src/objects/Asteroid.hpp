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

class Asteroid: public Object, public Drawable
{
public:
	Asteroid();
	virtual ~Asteroid();

	void initialize(const unsigned int planet);

	// Own functions
	/*
	 * XXX: Fuu.
	 */
	void move();

	// --- Box2D things ---
	inline b2Vec2 Position() const { return pos_; }
	inline void SetPosition(b2Vec2 p) { pos_ = p; }
	inline void SetBody(b2Body* b) { body_ = b; }

	// --- Drawable ---
	inline unsigned int sprite() const { return 11; }
	inline float angle() const { return 0.0; }
	inline b2Vec2 pos() const { return pos_; }
	inline b2Vec2 dimensions() const { return b2Vec2(10, 10); }

private:
	/*
	 * Asteroid doesn't own planet.
	 */
	unsigned int planet_;

	/*
	 * Velocity.
	 */
	b2Vec2 debris_;
	b2Vec2 velocity_;

	b2Vec2 pos_;

	b2Body* body_;
};

#endif /* ASTEROID_H_ */
