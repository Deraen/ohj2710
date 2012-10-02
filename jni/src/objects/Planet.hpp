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

class Planet: public Object
{
public:
	Planet();
	virtual ~Planet();

	void initialize(const unsigned int player);

	void reset_inner();

	// Own functions
	b2Vec2 getPos() const
	{
		return pos_;
	}

private:
	/*
	 * Planet doesn't own player.
	 */
	unsigned int player_;

	/*
	 * Planet owns hitbox.
	 */
	unsigned int hitbox_;

	/*
	 * Planet owns drawable.
	 */
	unsigned int drawable_;

	b2Vec2 pos_;
};

#endif /* PLANET_H_ */
