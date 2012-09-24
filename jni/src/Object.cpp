/*
 * Object.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: juho
 */

#include "Object.hpp"

Object::Object() {
	// TODO Auto-generated constructor stub
	reset();
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

void Object::reset()
{
	reset_inner();

	id_ = 0;
}

unsigned int Object::getId() const
{
	return id_;
}

bool Object::setId(const unsigned int i)
{
	// Debug
	if (id_ == 0)
	{
		/*
		 * Tried to set id for used object.
		 */
	}

	id_ = i;
}
