/*
 * Game.hh
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#ifndef GAME_HH_
#define GAME_HH_

#include <set>

#include "Box2D/Box2D.h"

#include "objects/Bomb.hpp"

class Laser;
class Asteroid;
class Planet;

class Game: public b2ContactListener {
public:
	enum Events {
		COLLISION_ASTEROID_PLANET,
		COLLISION_BOMB_PLANET,
		COLLISION_ASTEROID_BOMB,
		DELETE_BODY,
		REPLENISH_WEAPON,
		USE_WEAPON,
		SPAWN_ASTEROID,
		SLOW_ASTEROID,
		STOP_LASER_FUU
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

	bool WeaponHasUses() const;
	void UseWeapon();
	inline void SelectWeapon(const Bomb::BombType weapon) { selectedWeapon_ = weapon; }

	void BeginContact(b2Contact* contact);
	// void EndContact(b2Contact* contact);

	void HandleEvent(SDL_Event& event);

	inline int Points() const { return points_; }
	void addPoint() { points_ += 1; }
	void removePoint() { points_ -= 1; }
	inline Bomb::BombType SelectedWeapon() const { return selectedWeapon_; }
	unsigned int BombCount(Bomb::BombType type) const;

	void DestroyBody(b2Body* body);

	enum Levels {
		LVL1,
		LVL2,
		LVL3,
		INF,
		COUNT_
	};

	static unsigned int* WeaponQuotas(unsigned int normal, unsigned int splash, unsigned int chain, unsigned int laser) {
		unsigned int* fuu = new unsigned int[Bomb::BombType::COUNT_];
		fuu[0] = normal;
		fuu[1] = splash;
		fuu[2] = chain;
		fuu[3] = laser;
		return fuu;
	};

	struct Level {
		std::string name;
		std::string planet;
		float g;
		unsigned int quota[Bomb::BombType::COUNT_];
		unsigned int rand;
		unsigned int asteroids;
		float asteroidForce;

		Level(std::string name_, std::string planet_, float g_, unsigned int quota_[Bomb::BombType::COUNT_], unsigned int rand_, unsigned int asteroids_, float asteroidForce_):
			name(name_),
			planet(planet_),
			g(g_),
			rand(rand_),
			asteroids(asteroids_),
			asteroidForce(asteroidForce_)
		{};
	};

	static const Level LEVELS[];

	void SelectLevel(Levels level);
	const Level* LevelInfo() const { return &LEVELS[level_]; }
	inline Levels SelectedLevel() const { return level_; }

private:
	b2World world_;

	Levels level_;
	Planet* planet_;

	bool running_;
	int points_;

	Bomb::BombType selectedWeapon_;
	unsigned int bombs_[Bomb::BombType::COUNT_];

	std::set<b2Body*> deleted_;

	static b2Filter bombFilter_;
};

#endif /* GAME_HH_ */
