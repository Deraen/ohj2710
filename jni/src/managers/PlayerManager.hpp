/*
 * PlayerManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef PLAYERMANAGER_HPP_
#define PLAYERMANAGER_HPP_

#include "../Manager.hpp"
#include "../objects/Player.hpp"

class PlayerManager: public Manager<Player> {
public:
	PlayerManager():
		Manager(5)
	{
	}

	virtual ~PlayerManager()
	{
	}

	static PlayerManager& instance()
	{
		static PlayerManager instance_;
		return instance_;
	}
};

#endif /* PLAYERMANAGER_HPP_ */
