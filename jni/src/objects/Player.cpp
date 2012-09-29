/*
 * Player.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "Player.hpp"
#include "Planet.hpp"
#include "../managers/PlanetManager.hpp"

Player::Player()
{
	// TODO Auto-generated constructor stub
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

void Player::reset_inner()
{
	if (planet_ != 0)
	{
		PlanetManager::instance().releaseObject(planet_);
	}
	planet_ = 0;
}

void Player::initialize(const std::string& name)
{
	name_ = name;

	planet_ = PlanetManager::instance().newObject();
	Planet* planet = PlanetManager::instance().getObject(planet_);
	// Tell planet which player resides in it.
	planet->initialize(getId());
}
