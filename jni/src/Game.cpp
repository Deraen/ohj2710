/*

 * Game.cc
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#include "Game.hpp"

#include "objects/Planet.hpp"
#include "objects/Asteroid.hpp"
#include "objects/Bomb.hpp"
#include "objects/Laser.hpp"
#include "Screen.hpp"
#include "interfaces/Timed.hpp"

const Game::Level Game::LEVELS[] = {
	Game::Level(
		"Lvl1", // Level name
		"MOON", // Planet name
		0.08, // Gravity
		100, 5, 0, 0,
		1, // Rand
		70, // Asteroids
		3, // Asteroid initial force
		2000, // Sec
		35
	),
	Game::Level(
		"Lvl2", // Level name
		"EARTH", // Planet name
		0.45, // Gravity
		20, 30, 5, 20,
		1, // Rand
		100, // Asteroids
		8, // Asteroid initial force
		1400,
		20
	),
	Game::Level(
		"Lvl3", // Level name
		"JUPITER", // Planet name
		1.2, // Gravity
		10, 10, 20, 20,
		1, // Rand
		150, // Asteroids
		15, // Asteroid initial force
		600,
		5
	),
	Game::Level(
		"N+1", // Level name
		"DEATHSTAR", // Planet name
		0.45, // Gravity
		0, 0, 0, 0,
		1, // Rand
		-1, // Asteroids
		8, // Asteroid initial force
		400, // Gets faster - implemented elsewhere
		0
	)
};

Game::Game():
	world_(b2Vec2(0.0, 0.0)),
	running_(true),
	planet_(NULL),
	level_(Levels::COUNT_)
{
	for (unsigned int i = 0; i < Bomb::BombType::COUNT_; ++i)
	{
		bombs_[i] = 0;
	}
}

Game::~Game()
{
}

void Game::init()
{
	world_.SetContactListener(this);
}

void Game::loop()
{
	while(running_)
	{
		deleted_.clear();

		Screen::instance().draw();

		Step();

		Screen::instance().processInput();

		// Give other applications some time to execute.
		SDL_Delay(20);
	}
}

void Game::Step()
{
	static const float DESTROYRADIUS = 150 * 150;

	world_.Step(1.0 / 60.0, 10, 10);
	world_.ClearForces();

	if (planet_ == NULL) return;

	b2Vec2 planetPoint = planet_->GetBody()->GetPosition();

	// All bodies affect all others bodies
	b2Body* body = world_.GetBodyList();
	while (body != NULL)
	{
		Object* obj = (Object*)body->GetUserData();
		float m1 = obj->GetMass();
		b2Vec2 p1 = body->GetPosition();

		b2Body* body2 = world_.GetBodyList();
		while (m1 != 0 && body2 != NULL)
		{
			Object* obj2 = (Object*)body2->GetUserData();
			float m2 = obj2->GetMass();

			if (m2 != 0 && body2->GetType() != b2_staticBody && body != body2)
			{
				b2Vec2 d = p1 - body2->GetPosition();
				float len = d.LengthSquared();
				// Strange things could happend if two bombs are over each other
				if (len > 0.01) {
					d.Normalize();
					d *= (LevelInfo()->g * m1 * m2) / len;

					body2->ApplyForceToCenter(d);
				}
			}
			body2 = body2->GetNext();
		}

		// Slow asteroids
		Timed* timed = dynamic_cast<Timed*>(obj);
		if (timed != NULL)
		{
			timed->Tick();
		}

		// Remove bodies that go too far away
		if ((planetPoint - body->GetPosition()).LengthSquared() > DESTROYRADIUS) {
			SDL_Event event;
			event.type = SDL_USEREVENT;
			event.user.code = Game::DELETE_BODY;
			event.user.data1 = body;
			SDL_PushEvent(&event);
		}

		body = body->GetNext();
	}
}

bool Game::WeaponHasUses() const
{
	return bombs_[selectedWeapon_] > 0;
}

void Game::UseWeapon()
{
	if (bombs_[selectedWeapon_] > 0)
	{
		bombs_[selectedWeapon_] -= 1;
	}
}

void Game::BeginContact(b2Contact *contact)
{
	b2Body* b1 = contact->GetFixtureA()->GetBody();
	b2Body* b2 = contact->GetFixtureB()->GetBody();
	Object* obj1 = (Object*)b1->GetUserData();
	Object* obj2 = (Object*)b2->GetUserData();

	SDL_Event event;
	event.type = SDL_USEREVENT;

	// Planet is static, it won't collide with others
	if (dynamic_cast<Asteroid*>(obj1) != NULL && dynamic_cast<Planet*>(obj2))
	{
		SDL_Log("Contact: Asteroid <-> Planet");
		event.user.code = COLLISION_ASTEROID_PLANET;
	}
	else if (dynamic_cast<Bomb*>(obj1) != NULL && dynamic_cast<Planet*>(obj2))
	{
		SDL_Log("Contact: Bomb <-> Planet");
		event.user.code = COLLISION_BOMB_PLANET;
	}
	else if (dynamic_cast<Asteroid*>(obj1) != NULL && dynamic_cast<Bomb*>(obj2))
	{
		SDL_Log("Contact: Asteroid <-> Bomb");
		event.user.code = COLLISION_ASTEROID_BOMB;
	}
	else if (dynamic_cast<Bomb*>(obj1) != NULL && dynamic_cast<Asteroid*>(obj2))
	{
		SDL_Log("Contact: Asteroid <-> Bomb");
		event.user.code = COLLISION_ASTEROID_BOMB;
		// invert bodies
		b2Body* tmp = b1;
		b1 = b2;
		b2 = tmp;
	}
	else
	{
		return;
	}

	event.user.data1 = b1;
	event.user.data2 = b2;

	SDL_PushEvent(&event);
}

void Game::HandleEvent(SDL_Event &event)
{
	if (event.user.code == COLLISION_ASTEROID_PLANET)
	{
		RemovePoint();

		DestroyBody((b2Body*)event.user.data1);
	}
	else if (event.user.code == COLLISION_BOMB_PLANET)
	{
		RemovePoint();

		DestroyBody((b2Body*)event.user.data1);
	}
	else if (event.user.code == COLLISION_ASTEROID_BOMB)
	{
		// blow up bomb
		((Bomb*)((b2Body*)event.user.data2)->GetUserData())->Detonate((b2Body*)event.user.data1);
	}
	else if (event.user.code == DELETE_BODY)
	{
		DestroyBody((b2Body*)event.user.data1);
	}
	else if (event.user.code == REPLENISH_WEAPON)
	{
		Bomb::BombType type = (Bomb::BombType)(long)event.user.data1;
		bombs_[type] += 1;

		if (bombs_[type] > Bomb::INFO[type].quota)
		{
			bombs_[type] = Bomb::INFO[type].quota;
		}
	}
	else if (event.user.code == SPAWN_ASTEROID)
	{
		if (asteroids_ == -1 || asteroids_ > 0) {
			new Asteroid((b2Body*)event.user.data1);
			if (asteroids_ != -1) {
				asteroids_ -= 1;
			}
		}
	}
}

unsigned int Game::BombCount(Bomb::BombType type) const
{
	return bombs_[type];
}

void Game::DestroyBody(b2Body* body)
{
	// Prevent double deletion
	auto f = deleted_.find(body);
	if (f != deleted_.end()) return;

	deleted_.insert(body);

	Object* obj = (Object*)body->GetUserData();
	delete obj;

	world_.DestroyBody(body);
}

void Game::AddPoint()
{
	if (level_ == Levels::INF) {
		points_ += 1;
	}
}

void Game::RemovePoint()
{
	points_ -= 1;

	if (points_ < 1 && level_ != Levels::INF)
	{
		SelectLevel(Levels::COUNT_);
	}
}

namespace {
	Uint32 SpawnAsteroid(Uint32 interval, void* param)
	{
		if (Game::instance().Asteroids() == -1 || Game::instance().Asteroids() > 0) {
			SDL_Event event;
			event.type = SDL_USEREVENT;
			event.user.code = Game::SPAWN_ASTEROID;
			event.user.data1 = param;

			SDL_PushEvent(&event);
			return interval;
		}
		else
		{
			return 0;
		}
	}

	Uint32 Replenish(Uint32 interval, void* param)
	{
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::REPLENISH_WEAPON;
		event.user.data1 = param;

		SDL_PushEvent(&event);

		return interval;
	}
}

void Game::SelectLevel(Game::Levels level)
{
	level_ = level;

	// Destroying all bodies should also delete current planet_
	b2Body* body = world_.GetBodyList();
	while (body != NULL)
	{
		DestroyBody(body);
		body = body->GetNext();
	}

	for (unsigned int i = 0; i < Bomb::BombType::COUNT_; ++i)
	{
		bombs_[i] = 0;
	}

	points_ = 0;

	SDL_RemoveTimer(asteroidTimer_);
	SDL_RemoveTimer(normalTimer_);
	SDL_RemoveTimer(splashTimer_);
	SDL_RemoveTimer(chainTimer_);
	SDL_RemoveTimer(laserTimer_);

	planet_ = NULL;
	if (level_ != Levels::COUNT_) {
		points_ = LevelInfo()->lives;
		asteroids_ = LevelInfo()->asteroids;

		bombs_[Bomb::BombType::NORMAL] = LevelInfo()->normal;
		bombs_[Bomb::BombType::SPLASH] = LevelInfo()->splash;
		bombs_[Bomb::BombType::CHAIN] = LevelInfo()->chain;
		bombs_[Bomb::BombType::LASER] = LevelInfo()->laser;

		if (level_ == Levels::INF)
		{
			srand(time(NULL));

			normalTimer_ = SDL_AddTimer(5000, Replenish, (void*)Bomb::BombType::NORMAL);
			splashTimer_ = SDL_AddTimer(10000, Replenish, (void*)Bomb::BombType::SPLASH);
			chainTimer_ = SDL_AddTimer(10000, Replenish, (void*)Bomb::BombType::CHAIN);
			laserTimer_ = SDL_AddTimer(1000, Replenish, (void*)Bomb::BombType::LASER);
		}
		else
		{
			srand(LevelInfo()->rand);
		}

		planet_ = new Planet(LevelInfo()->planet);

		asteroidTimer_ = SDL_AddTimer(LevelInfo()->asteroidSpawnSec, SpawnAsteroid, planet_->GetBody());
	}
}
