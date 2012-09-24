/*
 * Player.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "Object.hpp"

class Player: public Object {
public:
	Player();
	virtual ~Player();

	void reset_inner();

	void initialize(const std::string& name);

private:
	std::string name_;

	/*
	 * Players planet.
	 *
	 * Player owns his planet.
	 */
	unsigned int planet_;
};

#endif /* PLAYER_H_ */
