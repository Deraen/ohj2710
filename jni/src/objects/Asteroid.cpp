/*
 * Asteroid.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include <cstdlib>
#include <cmath>

#include "objects/Asteroid.hpp"
#include "Game.hpp"
#include "objects/Planet.hpp"
#include "Assets.hpp"

unsigned int Asteroid::count_ = 0;

namespace {
	Uint32 SlowEvent(Uint32 interval, void* param)
	{
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::SLOW_ASTEROID;
		event.user.data1 = param;

		SDL_PushEvent(&event);

		return interval;
	}
}

Asteroid::Asteroid(b2Body* planet):
	Object(),
	Drawable()
{
	type_ = Assets::instance().info("Asteroid", "NORMAL");

	// Random number between 0 and 2*PI
	float pos = (rand() % 2000) * M_PI / 1000.0;

	// Init Box2D
	b2BodyDef temp;
	temp.position = planet->GetPosition() + b2Vec2(7.0 * std::cos(pos), 7.0 * std::sin(pos));
	temp.type = b2_dynamicBody;
	CreateBody(temp, type_.def);

	pos -= M_PI / 2;

	float f = Game::instance().LevelInfo()->asteroidForce;
	GetBody()->ApplyForce(b2Vec2(f * std::cos(pos), f * std::sin(pos)), GetBody()->GetWorldCenter());
	SDL_Log("Asteroid m=%f @(%f, %f)", GetBody()->GetMass(), GetBody()->GetPosition().x, GetBody()->GetPosition().y);

	timer_ = SDL_AddTimer(1000, SlowEvent, this);

	++count_;
}

Asteroid::~Asteroid()
{
	SDL_RemoveTimer(timer_);

	--count_;
	SDL_Log("~Asteroid");
}

void Asteroid::Slow()
{
	b2Vec2 f = GetBody()->GetLinearVelocity();
	// Asteroids lose 0.4% of their velocity / second
	f *= -0.004;
	GetBody()->ApplyForce(f, GetBody()->GetWorldCenter());
}
