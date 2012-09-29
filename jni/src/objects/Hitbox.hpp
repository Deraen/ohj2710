/*
 * Hitbox.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include "../Object.hpp"

class Hitbox: public Object {
public:
	Hitbox();
	virtual ~Hitbox();

	void reset_inner();
private:
	/*
	 * Position.
	 */
	float x_;
	float y_;
};

#endif /* HITBOX_HPP_ */
