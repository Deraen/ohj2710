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

unsigned int Bomb::count_ = 0;

Bomb::Bomb(b2Body* parent, float radians, float force):
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

	Planet* planet = (Planet*)parent->GetUserData();
	float r = planet->GetRadius() + 1.0;

	b2BodyDef temp;
	temp.position = parent->GetPosition() + b2Vec2(r * std::cos(radians), r * std::sin(radians));
	temp.type = b2_dynamicBody;
	temp.angle = radians;
	CreateBody(temp, type_.def);

	force *= 10;
	GetBody()->ApplyForce(b2Vec2(force  * std::cos(radians), force * std::sin(radians)), GetBody()->GetWorldCenter());
	GetBody()->SetBullet(true);
	SDL_Log("Bomb created (%f, %f)", GetBody()->GetPosition().x, GetBody()->GetPosition().y);

	++count_;
}

Bomb::~Bomb()
{
	--count_;
	SDL_Log("~Bomb");
}
