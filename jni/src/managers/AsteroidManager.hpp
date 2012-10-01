/*
 * AsteroidManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef ASTEROIDMANAGER_HPP_
#define ASTEROIDMANAGER_HPP_

#include "Manager.hpp"
#include "objects/Asteroid.hpp"

class AsteroidManager: public Manager<Asteroid>
{
public:
	AsteroidManager():
		Manager(100)
	{
	}

	virtual ~AsteroidManager()
	{
	}

	static AsteroidManager& instance()
	{
		static AsteroidManager instance_;
		return instance_;
	}
};

#endif /* ASTEROIDMANAGER_HPP_ */
