/*
 * Bomb.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "Assets.hpp"
#include "Bomb.hpp"
#include "Game.hpp"
#include "interfaces/Drawable.hpp"
#include "objects/Planet.hpp"

const std::string Bomb::TYPENAMES[] = {"NORMAL", "SPLASH", "CHAIN", "LASER"};

Bomb::Bomb(b2Body* planet, BombType type, float radians, float force):
	Object(),
	Drawable(),
	body_(),
	type_(),
	type__(type)
{
	type_ = Assets::instance().info("Bomb", TYPENAMES[type]);

	b2BodyDef temp;
	temp.userData = this;
	// XXX: ask planet body for the radius
	temp.position = planet->GetPosition() + b2Vec2(Planet::RADIUS * std::cos(radians), Planet::RADIUS * std::sin(radians));
	temp.type = b2_dynamicBody;
	temp.angle = radians;
	body_ = Game::instance().world()->CreateBody(&temp);

	body_->CreateFixture(type_.def);

	force *= 10;
	body_->ApplyForce(b2Vec2(force  * std::cos(radians), force * std::sin(radians)), body_->GetWorldCenter());
	body_->SetBullet(true);
	SDL_Log("Bomb created (%f, %f)", body_->GetPosition().x, body_->GetPosition().y);
}

Bomb::~Bomb()
{
}
