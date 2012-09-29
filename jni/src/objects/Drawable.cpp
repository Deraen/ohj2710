/*
 * Drawable.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#include "Drawable.hpp"

Drawable::Drawable() {
	// TODO Auto-generated constructor stub

}

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

void Drawable::reset_inner()
{
}

void Drawable::initialize(DrawableType type)
{
	type_ = type;
}

void Drawable::circle(float r)
{
	r_ = r;
}

void Drawable::draw() const
{
	if (type_ == CIRCLE)
	{
		
	}
}
