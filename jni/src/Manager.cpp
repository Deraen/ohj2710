/*
 * Manager.h
 *
 *  Created on: Sep 24, 2012
 *      Author: juho
 */

#include <queue>
#include <map>
#include <functional>

#include "SDL_log.h"

#include "Object.hpp"
#include "Manager.hpp"

Manager::Manager():
	id_(0)
{
}

Manager::~Manager()
{
}

Manager& Manager::instance()
{
	static Manager instance_;
	return instance_;
}

/*
 * Releases object by id.
 */
bool Manager::releaseObject(const unsigned int i)
{
	auto find = objects_.find(i);

	if (find != objects_.end())
	{
		Object* obj = find->second;
		objects_.erase(find);

		// obj->reset();
		delete obj;

		SDL_Log("Released object %i", i);

		return true;
	}
	return false;
}
