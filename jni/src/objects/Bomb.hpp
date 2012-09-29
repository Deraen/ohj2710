/*
 * Bomb.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "../Object.hpp"

class Bomb: public Object {
public:
	enum BombType {
		NORMAL,
		SPLASH,
		CHAINREACTION
	};

	Bomb();
	virtual ~Bomb();

	void initialize(const unsigned int player, const unsigned int planet, BombType type);

	void reset_inner();

private:
	/*
	 * Bomb doesn't own player.
	 */
	unsigned int player_;

	/*
	 * Bomb doesn't own planet.
	 */
	unsigned int planet_;

	/*
	 * Bomb owns hitbox.
	 */
	unsigned int hitbox_;

	/*
	 *
	 */
	BombType type_;

	/*
	 * Velocity.
	 */
	float dx_;
	float dy_;
};

#endif /* BOMB_H_ */
