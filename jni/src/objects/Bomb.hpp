/*
 * Bomb.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "Object.hpp"

class Bomb: public Object
{
public:
	enum BombType {
		NORMAL,
		SPLASH,
		CHAINREACTION
	};

	Bomb();
	virtual ~Bomb();

	void initialize(const unsigned int planet, BombType type);

	void reset_inner();

private:
	/*
	 * Bomb doesn't own planet.
	 */
	unsigned int planet_;

	/*
	 *
	 */
	BombType type_;
};

#endif /* BOMB_H_ */
