/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL_log.h"
#include "SDL2_gfxPrimitives.h"

#include "objects/Planet.hpp"
#include "Game.hpp"
#include "objects/Asteroid.hpp"
#include "Assets.hpp"
#include "objects/Bomb.hpp"
#include "Screen.hpp"

const float Planet::RADIUS = 2.0;

Planet::Planet():
	Object(),
	Drawable(),
	Touchable()
{
	type_ = Assets::instance().info("Planet", "EARTH");

	b2BodyDef temp;
	temp.userData = this;
	temp.position = b2Vec2(0.0, 0.0);
	// temp.type = b2_staticBody;
	temp.type = b2_dynamicBody; // Fuu. planet should be static, but static bodies have no weight
	body_ = Game::instance().world()->CreateBody(&temp);

	body_->CreateFixture(type_.def);

	SDL_Log("Planet m=%f", body_->GetMass());

	for (unsigned int i = 0; i < 8; ++i)
	{
		new Asteroid(body_);
	}
}

Planet::~Planet()
{
}

void Planet::Draw(b2Body* body) const
{
	Drawable::Draw(body);

	if (touched_)
	{
		b2Vec2 p1 = Screen::instance().toPixels(body->GetPosition(), true);
		Sint16 x1 = static_cast<Sint16>(p1.x);
		Sint16 y1 = static_cast<Sint16>(p1.y);

		b2Vec2 p2 = Screen::instance().toPixels(touchPosition_ - body->GetPosition());
		Sint16 x2 = x1 - static_cast<Sint16>(p2.x);
		Sint16 y2 = y1 - static_cast<Sint16>(p2.y);
		thickLineRGBA(Screen::instance().renderer(), x1, y1, x2, y2, 4, 200, 0, 150, 255);
	}
}

void Planet::TouchStart()
{
	touched_ = true;
}

void Planet::TouchMovement(const b2Vec2 &p)
{
	touchPosition_ = p;
}

void Planet::TouchEnd()
{
	touched_ = false;

	b2Vec2 d = touchPosition_ - body_->GetPosition();

	float force = d.Length();

	d.Normalize();

	float radians = atan2(-d.y, -d.x);

	new Bomb(body_, radians, force);
}
