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
	};

	Game();

	virtual ~Game();

	void init();

	void loop();

	inline void Stop() { running_ = false; }

	static Game& instance()
	{
		static Game instance_;
		return instance_;
	}

	void Step();

	inline b2World* World() { return &world_; }

	bool WeaponHasUses() const;
	void UseWeapon();
	inline void SelectWeapon(const Bomb::BombType weapon) { selectedWeapon_ = weapon; }

	void BeginContact(b2Contact* contact);

	void HandleEvent(SDL_Event& event);

	inline int Points() const { return points_; }
	void AddPoint();
	void RemovePoint();
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

	struct Level {
		std::string name;
		std::string planet;
		float g;
		unsigned int bombs[Bomb::BombType::COUNT_];
		unsigned int rand;
		int asteroids;
		float asteroidForce;
		unsigned int asteroidSpawnSec;
		unsigned int lives;

		Level(std::string name_,
		      std::string planet_,
		      float g_,
		      unsigned int normal_,
		      unsigned int splash_,
		      unsigned int chain_,
		      unsigned int laser_,
		      unsigned int rand_,
		      int asteroids_,
		      float asteroidForce_,
		      unsigned int asteroidsSpawnSec_,
		      unsigned int lives_):
			name(name_),
			planet(planet_),
			g(g_),
			bombs{normal_, splash_, chain_, laser_},
			rand(rand_),
			asteroids(asteroids_),
			asteroidForce(asteroidForce_),
			asteroidSpawnSec(asteroidsSpawnSec_),
			lives(lives_)
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
	int asteroids_;

	bool running_;
	int points_;

	Bomb::BombType selectedWeapon_;
	unsigned int bombs_[Bomb::BombType::COUNT_];

	std::set<b2Body*> deleted_;

	static b2Filter bombFilter_;

	unsigned int previousReplenish_[Bomb::BombType::COUNT_];
	unsigned int previousAsteroid_;
};

#endif /* GAME_HH_ */
