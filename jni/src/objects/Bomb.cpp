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
	int a = rand() % 2;
	if (a == 0)
	{
		type_ = Assets::instance().info("Bomb", "NORMAL");
	}
	else
	{
		type_ = Assets::instance().info("Bomb", "SPLASH");
	}

	float pos = (rand() % 2000) * M_PI / 1000.0;

	b2BodyDef temp;
	temp.userData = this;
	temp.position = planet->GetPosition() + b2Vec2(Planet::RADIUS * std::cos(pos), Planet::RADIUS * std::sin(pos));
	temp.type = b2_dynamicBody;
	temp.angle = pos;
	body_ = Game::instance().world()->CreateBody(&temp);

	body_->CreateFixture(type_.def);

	body_->ApplyForce(b2Vec2(4.0 * std::cos(pos), 4.0 * std::sin(pos)), body_->GetWorldCenter());
	body_->SetBullet(true);
	SDL_Log("Bomb created (%f, %f)", body_->GetPosition().x, body_->GetPosition().y);
}

Bomb::~Bomb()
{
}
