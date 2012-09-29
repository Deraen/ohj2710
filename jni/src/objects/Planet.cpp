/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "Planet.hpp"
#include "../managers/DrawableManager.hpp"

Planet::Planet() {
	// TODO Auto-generated constructor stub

}

Planet::~Planet() {
	// TODO Auto-generated destructor stub
}


void Planet::initialize(const unsigned int player) {
	player_ = player;

	drawable_ = DrawableManager::instance().newObject();
	Drawable* obj = DrawableManager::instance().getObject(drawable_);
	obj->initialize(Drawable::CIRCLE);
	obj->circle(100.0);
}

void Planet::reset_inner() {

}
