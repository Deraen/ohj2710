/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL_log.h"

#include "objects/Planet.hpp"
#include "Game.hpp"
#include "objects/Asteroid.hpp"
#include "Assets.hpp"
#include "objects/Bomb.hpp"

const float Planet::RADIUS = 2.0;

Planet::Planet():
	Object(),
	Drawable(),
	Touchable()
{
	sprite_ = Object::sprite("earth");

	b2BodyDef temp;
	temp.userData = this;
	temp.position = b2Vec2(0.0, 0.0);
	temp.type = b2_staticBody;
	body_ = Game::instance().world()->CreateBody(&temp);

	b2FixtureDef def = Object::fixtureDef("earth");

	body_->CreateFixture(&def);

	for (unsigned int i = 0; i < 8; ++i)
	{
		new Asteroid(body_);
	}
}

Planet::~Planet()
{
}

void Planet::touched(const b2Vec2 &touchPosition)
{
	SDL_Log("Planet has been touched!");
	new Bomb(body_);
}
