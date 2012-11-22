/*
 * Game.hh
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#ifndef GAME_HH_
#define GAME_HH_

#include "Box2D/Box2D.h"

#include "objects/Bomb.hpp"

class Game {
public:
	Game();

	virtual ~Game();

	void init();

	void loop();

	inline void stop() { running_ = false; }

	static Game& instance()
	{
		static Game instance_;
		return instance_;
	}

	void Step();

	inline b2World* world() { return &world_; }

	void Shoot(b2Body* planet, float radians, float force);
	inline void SelectWeapon(const Bomb::BombType weapon) { selectedWeapon_ = weapon; }

private:
	b2World world_;

	bool running_;

	Bomb::BombType selectedWeapon_;
};

#endif /* GAME_HH_ */
