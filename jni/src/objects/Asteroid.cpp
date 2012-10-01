/*
 * Asteroid.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include <cstdlib>
#include <cmath>

#include "Asteroid.hpp"
#include "managers/DrawableManager.hpp"
#include "managers/PlanetManager.hpp"

Asteroid::Asteroid() {
	// TODO Auto-generated constructor stub

}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::reset_inner()
{

}

void Asteroid::initialize(const unsigned int planet)
{
	planet_ = planet;

	// Random number between 0 and 2*PI
	float pos = (rand() % 2000) * M_PI / 1000.0;

	// Init pos
	pos_.x = 200 * std::cos(pos);
	pos_.y = 200 * std::sin(pos);

	drawable_ = DrawableManager::instance().newObject();
	DrawableManager::instance().withObject(drawable_, [this](Drawable* obj)
	{
		obj->initialize(pos_, b2Vec2(10, 10));
	});

	// Init speed
	// Distance from planet to asteroid
	b2Vec2 ppos;
	PlanetManager::instance().withObject(planet_, [&](Planet* obj)
	{
		ppos = obj->getPos();
	});

	b2Vec2 vec = ppos - pos_;
	float len = vec.Length();
	vel_ = b2Vec2(-vec.y / len, vec.x / len);

	// Random...
	vel_ *= 2.58;
}

void Asteroid::move()
{
	// Etäisyys planeettaan
	b2Vec2 ppos;
	PlanetManager::instance().withObject(planet_, [&](Planet* obj)
	{
		ppos = obj->getPos();
	});

	b2Vec2 vec = ppos - pos_;
	float len = vec.LengthSquared();

	const float gravity = 6.67e-11;
	const float mass_planet = 100000000;
	const float mass_asteroid = 1000;

	float32 force = (gravity * mass_planet * mass_asteroid) / len;
	vec *= force;
	vel_ += vec;

	pos_ += vel_;

	DrawableManager::instance().withObject(drawable_, [this](Drawable* obj)
	{
		obj->updatePos(pos_);
	});
}
