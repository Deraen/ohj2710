/*
 * Bomb.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL2_gfxPrimitives.h"

#include "Assets.hpp"
#include "Bomb.hpp"
#include "Game.hpp"
#include "interfaces/Drawable.hpp"
#include "objects/Planet.hpp"
#include "Screen.hpp"

// Quota and replenish time affect inf game mode
const Bomb::Info Bomb::INFO[] = {
	{"NORMAL", 15, 5000},
	{"SPLASH", 5, 10000},
	{"CHAIN", 5, 10000},
	{"LASER", 10, 1000}
};

unsigned int Bomb::count_ = 0;


// All bombs on same collision group. Negative numbers means that objects
// with same group never collide with each other.
b2Filter bombFilter_;

Bomb::Bomb(b2Body* parent, BombType type, float radians, float force):
	Object(),
	Drawable(),
	type_(),
	type__(type),
	status_(DEFAULT),
	previous_(SDL_GetTicks())
{
	bombFilter_.groupIndex = -1;

	type_ = Assets::instance().info("Bomb", INFO[type].name);

	Planet* planet = (Planet*)parent->GetUserData();
	float r = planet->GetRadius() + 1.0;

	b2BodyDef temp;
	temp.position = parent->GetPosition() + b2Vec2(r * std::cos(radians), r * std::sin(radians));
	temp.type = b2_dynamicBody;
	temp.angle = radians;
	CreateBody(temp, type_.def);

	GetBody()->GetFixtureList()->SetFilterData(bombFilter_);

	force *= 10;
	GetBody()->ApplyForce(b2Vec2(force  * std::cos(radians), force * std::sin(radians)), GetBody()->GetWorldCenter());
	GetBody()->SetBullet(true);
	SDL_Log("Bomb created (%f, %f)", GetBody()->GetPosition().x, GetBody()->GetPosition().y);

	++count_;
}

Bomb::Bomb(BombType type, b2Vec2 pos, Status status):
	Object(),
	Drawable(),
	type_(),
	type__(type),
	status_(status),
	previous_(SDL_GetTicks())
{
	type_ = Assets::instance().info("Bomb", INFO[type].name);

	b2BodyDef temp;
	temp.position = pos;
	temp.type = b2_dynamicBody;
	temp.angle = 0;
	CreateBody(temp, type_.def);

	GetBody()->GetFixtureList()->SetFilterData(bombFilter_);

	GetBody()->SetBullet(true);
	SDL_Log("Bomb created (%f, %f)", GetBody()->GetPosition().x, GetBody()->GetPosition().y);

	++count_;
}

Bomb::~Bomb()
{
	--count_;
	SDL_Log("~Bomb");
}

void Bomb::Draw(b2Body *body) const
{
	if (status_ == DEFAULT)
	{
		Drawable::Draw(body);
	}
	else if (status_ == DETONATED)
	{
		b2Vec2 p = Screen::instance().toPixels(GetBody()->GetPosition(), true);
		Sint16 x = p.x;
		Sint16 y = p.y;
		unsigned int px = Screen::instance().pixelsPerMeter();
		auto render = Screen::instance().renderer();

		if (type__ == NORMAL)
		{
			filledCircleRGBA(render, x, y, 0.4 * px, 255, 0, 0, 255);
		}
		else if (type__ == SPLASH)
		{
			filledCircleRGBA(render, x, y, 0.6 * px, 255, 100, 0, 255);
		}
		else if (type__ == CHAIN)
		{
			filledCircleRGBA(render, x, y, 0.3 * px, 255, 0, 150, 255);
		}
	}
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
	// Shortcuts
	static auto DestroyFixture = [&]() {
		b2Fixture* fixture = GetBody()->GetFixtureList();
		if (fixture != NULL)
		{
			GetBody()->DestroyFixture(fixture);
		}
	};

	// What to do if asteroid hits explosion - "Special cases"
	if (status_ == DETONATED)
	{
		if (type__ == CHAIN)
		{
			// Create new chain bomb that is already detonated
			new Bomb(CHAIN, other->GetPosition(), DETONATED);
		}
		else if (type__ == NORMAL)
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

	// All bombs want to change fixture from bomb into explosion
	DestroyFixture();
	if (type__ == NORMAL)
	{
		// Normal bomb destroys hit asteroid immediatly
		// display small explosion for short time

		// Normal explosion doesn't have fixture at all.
	}
	else if (type__ == SPLASH)
	{
		// Display large explosion for some time and destroy asteroids that go through explosion

		// Modify body so that:
		// It wont move
		// It has circle collision shape (explosion)
		b2CircleShape circle;
		circle.m_radius = 0.6;

		b2FixtureDef def;
		def.shape = &circle;
		GetBody()->CreateFixture(&def);
		GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		GetBody()->SetAngularVelocity(0);
		GetBody()->GetFixtureList()->SetFilterData(bombFilter_);
	}
	else if (type__ == CHAIN)
	{
		// Modify body so that:
		// It wont move
		// It has circle collision shape (explosion)
		b2CircleShape circle;
		circle.m_radius = 0.3;

		b2FixtureDef def;
		def.shape = &circle;
		GetBody()->CreateFixture(&def);
		GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		GetBody()->SetAngularVelocity(0);
		GetBody()->GetFixtureList()->SetFilterData(bombFilter_);
	}
	previous_ = SDL_GetTicks();
}

void Bomb::Tick()
{
	if (status_ == DETONATED
	 && ((type__ == NORMAL && SDL_GetTicks() - previous_ > 500)
	  || (type__ == SPLASH && SDL_GetTicks() - previous_ > 1000)
	  || (type__ == CHAIN && SDL_GetTicks() - previous_ > 2000)))
	{
		SDL_Log("Destroying bomb (Timer)");
		// Destroy bomb after a delay
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::DELETE_BODY;
		event.user.data1 = GetBody();

		SDL_PushEvent(&event);
	}
}