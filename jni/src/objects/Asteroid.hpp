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

class Asteroid: public Object
{
public:
	Asteroid();
	virtual ~Asteroid();

	void initialize(const unsigned int planet);

	void reset_inner();

	// Own functions
	/*
	 * Fuu.
	 */
	void move();

	inline b2Vec2 Position() const { return pos_; }
	inline void SetPosition(b2Vec2 p) { pos_ = p; }
	inline void SetBody(b2Body* b) { body_ = b; }
private:
	/*
	 * Asteroid doesn't own planet.
	 */
	unsigned int planet_;

	/*
	 * Asteroid owns hitbox.
	 */
	unsigned int hitbox_;

	/*
	 * Asteroid has drawable.
	 */
	unsigned int drawable_;

	/*
	 * Velocity.
	 */
	b2Vec2 debris_;
	b2Vec2 velocity_;

	b2Vec2 pos_;

	b2Body* body_;
};

#endif /* ASTEROID_H_ */
