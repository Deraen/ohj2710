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

/*
 * A planet is a player.
 */
class Planet: public Object, public Drawable
{
public:
	Planet();
	virtual ~Planet();

	void initialize();

	// --- Drawable ---
	unsigned int sprite() const;
	inline float angle() const { return 0.0; }
	inline b2Vec2 pos() const { return pos_; }
	inline b2Vec2 dimensions() const { return b2Vec2(128, 128); }

private:
	std::string name;

	b2Vec2 pos_;
};

#endif /* PLANET_H_ */
