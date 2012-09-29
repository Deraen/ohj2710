/*
 * Asteroid.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "../Object.hpp"

class Asteroid: public Object {
public:
	Asteroid();
	virtual ~Asteroid();

	void initialize(const unsigned int planet);

	void reset_inner();

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
	 * Velocity.
	 */
	float dx_;
	float dy_;
};

#endif /* ASTEROID_H_ */
