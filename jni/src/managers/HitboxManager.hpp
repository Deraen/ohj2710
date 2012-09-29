/*
 * HitboxManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef HITBOXMANAGER_HPP_
#define HITBOXMANAGER_HPP_

#include "../Manager.hpp"
#include "../objects/Hitbox.hpp"

class HitboxManager: public Manager<Hitbox> {
public:
	HitboxManager():
		Manager(200)
	{
	}

	virtual ~HitboxManager()
	{
	}

	static HitboxManager& instance()
	{
		static HitboxManager instance_;
		return instance_;
	}
};

#endif /* HITBOXMANAGER_HPP_ */
