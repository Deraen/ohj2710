/*
 * PlanetManager.h
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef PLANETMANAGER_H_
#define PLANETMANAGER_H_

#include "../Manager.hpp"
#include "../objects/Planet.hpp"

class PlanetManager: public Manager<Planet> {
public:
	PlanetManager():
		Manager(5)
	{
	}

	virtual ~PlanetManager()
	{
	}

	static PlanetManager& instance()
	{
		static PlanetManager instance_;
		return instance_;
	}
};

#endif /* PLANETMANAGER_H_ */
