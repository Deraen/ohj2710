/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL_log.h"

#include "Planet.hpp"
#include "Manager.hpp"
#include "Assets.hpp"

Planet::Planet()
{
}

Planet::~Planet()
{
}


void Planet::initialize()
{
	pos_.x = 0.0;
	pos_.y = 0.0;
}

unsigned int Planet::sprite() const
{
	return Assets::instance().getSprite("earth");
}
