/*
 * Planet.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "../Object.hpp"

class Planet: public Object {
public:
	Planet();
	virtual ~Planet();

	void initialize(const unsigned int player);

	void reset_inner();

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
};

#endif /* PLANET_H_ */
