/*
 * Object.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: juho
 */

#include "SDL_log.h"

#include "Object.hpp"
#include "common.hpp"

Object::Object():
	id_(0)
{
	// TODO Auto-generated constructor stub
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

unsigned int Object::getId() const
{
	return id_;
}

void Object::setId(const unsigned int i)
{
	if (id_ != 0)
	{
		SDL_Log("Set id for object (%i) even though this object was in use.", id_);
	}

	id_ = i;
}
