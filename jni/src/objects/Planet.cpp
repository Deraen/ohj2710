/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL_log.h"

#include "Planet.hpp"
#include "Manager.hpp"

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
