
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

#include "objects/Bomb.hpp"

class Asteroid;

class Game: public b2ContactListener {
public:
	enum Events {
		COLLISION_ASTEROID_PLANET,
		COLLISION_BOMB_PLANET,
		COLLISION_ASTEROID_BOMB,
		COLLISION_BOMB_BOMB,
		DELETE_BODY,
		REPLENISH_BOMB
	};

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

	void BeginContact(b2Contact* contact);
	// void EndContact(b2Contact* contact);

	void HandleEvent(SDL_Event& event);

	inline Bomb::BombType SelectedWeapon() const { return selectedWeapon_; }
	unsigned int BombCount(Bomb::BombType type) const;

private:
	b2World world_;

	bool running_;

	Bomb::BombType selectedWeapon_;
	unsigned int bombs_[Bomb::BombType::COUNT_];
};

#endif /* GAME_HH_ */
