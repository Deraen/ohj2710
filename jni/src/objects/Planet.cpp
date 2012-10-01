/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL_log.h"

#include "Planet.hpp"
#include "managers/DrawableManager.hpp"

Planet::Planet()
{
	// TODO Auto-generated constructor stub

}

Planet::~Planet()
{
	// TODO Auto-generated destructor stub
}


void Planet::initialize(const unsigned int player)
{
	player_ = player;

	drawable_ = DrawableManager::instance().newObject();
	DrawableManager::instance().withObject(drawable_, [](Drawable* obj)
	{
		obj->initialize(b2Vec2(0, 0), b2Vec2(80, 80));
	});

	pos_.x = 0.0;
	pos_.y = 0.0;
}

void Planet::reset_inner() {
	DrawableManager::instance().releaseObject(drawable_);
}
