/*
 * Bomb.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include <cstdint>
#include "SDL.h"

#include "Assets.hpp"
#include "Bomb.hpp"
#include "Game.hpp"
#include "interfaces/Drawable.hpp"
#include "objects/Planet.hpp"
#include "Screen.hpp"

// Quota and replenish time affect inf game mode
const Bomb::Info Bomb::INFO[] = {
	// Name, Explosion Name, Quota, Replenish time, Explosion time
	{"NORMAL", "NORMALEXPLOSION", 15, 5000, 500},
	{"SPLASH","SPLASHEXPLOSION",  5, 10000, 1000},
	{"CHAIN", "CHAINEXPLOSION", 5, 10000, 2000},
	{"LASER", "DOES-NOT-EXIST", 10, 1000, 0}
};

unsigned int Bomb::count_ = 0;

// All bombs on same collision group. Negative numbers means that objects
// with same group never collide with each other.
b2Filter bombFilter_;

Bomb::Bomb(b2Body* parent, BombType type, float radians, float force):
	Object(),
	Drawable(),
	asset_(),
	type_(type),
	status_(DEFAULT),
	previous_(SDL_GetTicks())
{
	float r = ((Planet*)parent->GetUserData())->GetRadius() + 1.0;

	b2Vec2 pos = parent->GetPosition() + b2Vec2(r * std::cos(radians), r * std::sin(radians));
	init(pos);

	force *= 10;
	GetBody()->ApplyForce(b2Vec2(force  * std::cos(radians), force * std::sin(radians)), GetBody()->GetWorldCenter());
}

Bomb::Bomb(BombType type, b2Vec2 pos, Status status):
	Object(),
	Drawable(),
	asset_(),
	type_(type),
	status_(status),
	previous_(SDL_GetTicks())
{
	init(pos);
}

void Bomb::init(const b2Vec2& pos)
{
	bombFilter_.groupIndex = -1;

	std::string name = INFO[type_].name;
	if (status_ == DETONATED)
	{
		name = INFO[type_].explosionName;
	}
	asset_ = Assets::instance().info("Bomb", name);

	b2BodyDef temp;
	temp.position = pos;
	temp.type = b2_dynamicBody;
	temp.angle = 0;
	CreateBody(temp, asset_.def);

	GetBody()->GetFixtureList()->SetFilterData(bombFilter_);
	GetBody()->SetBullet(true);

	// SDL_Log("Bomb created (%f, %f)", GetBody()->GetPosition().x, GetBody()->GetPosition().y);
	++count_;
}

Bomb::~Bomb()
{
	--count_;
	// SDL_Log("~Bomb");
}

float Bomb::GetMass() const
{
	// Detonated bombs have mass of 0 so they wont move
	if (status_ == DETONATED)
	{
		return 0.0;
	}
	return Object::GetMass();
}

void Bomb::Detonate(b2Body* other)
{
	// What to do if asteroid hits explosion - "Special cases"
	if (status_ == DETONATED)
	{
		if (type_ == CHAIN)
		{
			// Create new chain bomb that is already detonated
			new Bomb(CHAIN, other->GetPosition(), DETONATED);
		}
		else if (type_ == NORMAL)
		{
			// Bomb might hit multiple asteroids but normal bomb will only
			// destroy one of them.
			return;
		}
	}

	// What to do if asteroid hit bomb
	// or explosion of splash or chain bomb
	Game::instance().AddPoint();

	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = Game::DELETE_BODY;
	event.user.data1 = other;

	SDL_PushEvent(&event);

	if (status_ == DETONATED)
	{
		return;
	}

	// Detonate bomb

	status_ = DETONATED;

	asset_ = Assets::instance().info("Bomb", INFO[type_].explosionName);

	b2Fixture* fixture = GetBody()->GetFixtureList();
	if (fixture != NULL)
	{
		GetBody()->DestroyFixture(fixture);
	}

	if (asset_.def != NULL)
	{
		GetBody()->CreateFixture(asset_.def);
		GetBody()->GetFixtureList()->SetFilterData(bombFilter_);
	}

	GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	GetBody()->SetAngularVelocity(0);
	previous_ = SDL_GetTicks();
}

void Bomb::Tick()
{
	if (status_ == DETONATED && SDL_GetTicks() - previous_ > INFO[type_].explosionTime)
	{
		// SDL_Log("Destroying bomb (Timer)");
		// Destroy bomb after a delay
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::DELETE_BODY;
		event.user.data1 = GetBody();

		SDL_PushEvent(&event);
	}
}
