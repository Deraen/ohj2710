/*
 * World.hh
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#ifndef WORLD_HH_
#define WORLD_HH_

#include "Box2D/Box2D.h"

class World {
public:
	World();

	virtual ~World();

	void Step();

private:

	b2World world_;
};

#endif /* WORLD_HH_ */
