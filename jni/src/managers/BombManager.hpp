/*
 * BombManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef BOMBMANAGER_HPP_
#define BOMBMANAGER_HPP_

#include "Manager.hpp"
#include "objects/Bomb.hpp"

class BombManager: public Manager<Bomb>
{
public:
	BombManager():
		Manager(100)
	{
	}

	virtual ~BombManager()
	{
	}

	static BombManager& instance()
	{
		static BombManager instance_;
		return instance_;
	}
};

#endif /* BOMBMANAGER_HPP_ */
