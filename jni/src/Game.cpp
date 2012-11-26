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
	new Planet();
}

void Game::loop()
{
	while(running_)
	{
		Screen::instance().draw();

		Step();

		Screen::instance().processInput();

		// Give other applications some time to execute.
		SDL_Delay(20);
	}
}

void Game::Step()
{
	static const float G = 2.66726;

	world_.Step(1.0 / 60.0, 10, 10);
	world_.ClearForces();

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
				float f = (G * m1 * m2) / d.LengthSquared();
				d.Normalize();
				d *= f;

				body2->ApplyForceToCenter(d);
			}
			body2 = body2->GetNext();
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
	else if (dynamic_cast<Bomb*>(obj1) != NULL && dynamic_cast<Bomb*>(obj2))
	{
		SDL_Log("Contact: Bomb <-> Bomb");
		event.user.code = COLLISION_BOMB_BOMB;
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

// void Game::EndContact(b2Contact *contact)
// {
// 	SDL_Log("Kosketus loppu");
// }

void Game::HandleEvent(SDL_Event &event)
{
	if (event.user.code == COLLISION_ASTEROID_PLANET)
	{
		removePoint();

		world_.DestroyBody((b2Body*)event.user.data1);
	}
	else if (event.user.code == COLLISION_BOMB_PLANET)
	{
		removePoint();

		world_.DestroyBody((b2Body*)event.user.data1);
	}
	else if (event.user.code == COLLISION_ASTEROID_BOMB)
	{
		// blow up bomb
		((Bomb*)((b2Body*)event.user.data2)->GetUserData())->Detonate((b2Body*)event.user.data1);
	}
	else if (event.user.code == COLLISION_BOMB_BOMB)
	{
		// Bombs are so smart that they'll only detonate if they hit asteroid
	}
	else if (event.user.code == DELETE_BODY)
	{
		world_.DestroyBody((b2Body*)event.user.data1);
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
}

unsigned int Game::BombCount(Bomb::BombType type) const
{
	return bombs_[type];
}
