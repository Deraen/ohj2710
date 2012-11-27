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

namespace {
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
Game::Game():
	world_(b2Vec2(0.0, 0.0)),
	running_(true)
{
	for (unsigned int i = 0; i < Bomb::BombType::COUNT_; ++i)
	{
		bombs_[i] = 0;
	}

	SDL_AddTimer(5000, Replenish, (void*)Bomb::BombType::NORMAL);
	SDL_AddTimer(10000, Replenish, (void*)Bomb::BombType::SPLASH);
	SDL_AddTimer(10000, Replenish, (void*)Bomb::BombType::CHAIN);
	SDL_AddTimer(1000, Replenish, (void*)Bomb::BombType::LASER);
}

Game::~Game()
{
}

void Game::init()
{
	world_.SetContactListener(this);
	planet_ = new Planet();
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
	static const float G = 0.45;
	static const float DESTROYRADIUS = 150 * 150;

	world_.Step(1.0 / 60.0, 10, 10);
	world_.ClearForces();

	b2Vec2 planetPoint = planet_->GetBody()->GetPosition();

	// All bodies affect all others bodies
	b2Body* body = world_.GetBodyList();
	while (body != NULL)
	{
		Object* obj = (Object*)body->GetUserData();
		float m1 = obj->GetMass();

		b2Body* body2 = world_.GetBodyList();
		while (m1 != 0 && body2 != NULL)
		{
			Object* obj2 = (Object*)body2->GetUserData();
			float m2 = obj2->GetMass();

			if (m2 != 0 && body2->GetType() != b2_staticBody && body != body2)
			{
				b2Vec2 d = body->GetPosition() - body2->GetPosition();
				float len = d.LengthSquared();
				// Strange things could happend if two bombs are over each other
				if (len > 0.01) {
					float f = (G * m1 * m2) / len;
					d.Normalize();
					d *= f;

					body2->ApplyForceToCenter(d);
				}
			}
			body2 = body2->GetNext();
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
	//if (dynamic_cast<Asteroid*>(obj1) != NULL && dynamic_cast<Asteroid*>(obj2)) {

	event.user.data1 = b1;
	event.user.data2 = b2;

	SDL_PushEvent(&event);
}

void Game::HandleEvent(SDL_Event &event)
{
	if (event.user.code == COLLISION_ASTEROID_PLANET)
	{
		removePoint();

		DestroyBody((b2Body*)event.user.data1);
	}
	else if (event.user.code == COLLISION_BOMB_PLANET)
	{
		removePoint();

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
		new Asteroid((b2Body*)event.user.data1);
	}
	else if (event.user.code == SLOW_ASTEROID)
	{
		Asteroid* asteroid = (Asteroid*)event.user.data1;
		asteroid->Slow();
	}
	else if (event.user.code == USE_WEAPON)
	{
		UseWeapon();
	}
	else if (event.user.code == STOP_LASER_FUU)
	{
		((Laser*)event.user.data1)->Deactivate();
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
