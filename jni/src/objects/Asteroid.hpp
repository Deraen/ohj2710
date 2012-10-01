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
	b2Vec2 vel_;

	b2Vec2 pos_;
};

#endif /* ASTEROID_H_ */
