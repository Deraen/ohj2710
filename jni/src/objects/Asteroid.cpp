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

Asteroid::Asteroid(b2Body* planet):
	Object(),
	Drawable()
{
	type_ = Assets::instance().info("Asteroid", "NORMAL");

	// Random number between 0 and 2*PI
	float pos = (rand() % 2000) * M_PI / 1000.0;

	// Init Box2D
	b2BodyDef temp;
	temp.userData = this;
	temp.position = planet->GetPosition() + b2Vec2(5.0 * std::cos(pos), 5.0 * std::sin(pos));
	temp.type = b2_dynamicBody;
	body_ = Game::instance().world()->CreateBody(&temp);

	body_->CreateFixture(type_.def);
	body_->ApplyForce(b2Vec2(11, 0.0), body_->GetWorldCenter());
	SDL_Log("Asteroid m=%f @(%f, %f)", body_->GetMass(), body_->GetPosition().x, body_->GetPosition().y);
}

Asteroid::~Asteroid()
{
}
