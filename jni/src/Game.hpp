/*
 * Game.hh
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#ifndef GAME_HH_
#define GAME_HH_

#include <queue>

#include "Box2D/Box2D.h"

class Asteroid;
class Bomb;

class Game: public b2ContactListener {
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

	void AsteroidAndBomb(Asteroid* asteroid, Bomb* bomb);
	void BeginContact(b2Contact* contact);
	// void EndContact(b2Contact* contact);

private:
	b2World world_;

	bool running_;

	std::queue<b2Body*> toDestroy_;
	std::queue<b2JointDef> jointsToCreate_;
};

#endif /* GAME_HH_ */
