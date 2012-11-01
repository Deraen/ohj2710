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

Bomb::Bomb(b2Body* planet):
	Object(),
	Drawable()
{
	sprite_ = Assets::instance().getSprite("bomb");

	float pos = (rand() % 2000) * M_PI / 1000.0;

	b2BodyDef temp;
	temp.userData = this;
	temp.position = planet->GetPosition() + b2Vec2(Planet::RADIUS * std::cos(pos), Planet::RADIUS * std::sin(pos));
	temp.type = b2_dynamicBody;
	temp.angle = pos + (M_PI / 2);
	body_ = Game::instance().world()->CreateBody(&temp);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.2, 0.2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.1f;

	body_->CreateFixture(&fixtureDef);

	body_->ApplyForce(b2Vec2(4.0 * std::cos(pos), 4.0 * std::sin(pos)), body_->GetWorldCenter());
	SDL_Log("Bomb created (%f, %f)", body_->GetPosition().x, body_->GetPosition().y);
}

Bomb::~Bomb()
{
}
