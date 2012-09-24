/*
 * Manager.h
 *
 *  Created on: Sep 24, 2012
 *      Author: juho
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <queue>
#include <map>

#include "Object.hpp"

template<typename T>
class Manager {
public:
	/*
	 * precreate: Define how many objects will be created when manager is initialized.
	 */
	Manager(const unsigned int precreate):
		id_(0)
	{
		for (unsigned int i = 0; i < precreate; ++i)
		{
			freeObjects_.push(new T);
		}
	}
	virtual ~Manager() {};

	/*
	 * Reserves object and returns id which can be used to access object.
	 *
	 * Id 0 is not used, first object gets id 1.
	 */
	unsigned int newObject() {
		id_++;

		if (!freeObjects_.empty())
		{
			// Debug
			if (freeObjects_.front()->getId() != 0) {
				/*
				 * Tried to use object which is not reseted properly (or it is used somewhere).
				 */
			}

			objects_[id_] = freeObjects_.front();
		}
		else
		{
			objects_[id_] = new T;
		}
		objects_[id_]->setId(id_);
		return id_;
	}

	/*
	 * Returns object by id.
	 *
	 * XXX: What to do when object with given id is not found? Preferably so
	 * that no checks (if object == NULL...) are needed where this is called.
	 */
	T* getObject(const unsigned int i) const {
		typename std::map<unsigned int, T*>::const_iterator find = objects_.find(i);

		if (find != objects_.end())
		{
			return find->second;
		}
		return NULL;
	}

	/*
	 * Releases object by id.
	 * Released objects are not destroyed but reseted and put back into queue for unused objects.
	 */
	bool releaseObject(const unsigned int i) {
		typename std::map<unsigned int, T*>::const_iterator find = objects_.find(i);

		if (find != objects_.end())
		{
			Object* obj = find->second;
			objects_.erase(find);

			obj->reset();
			freeObjects_.push(obj);
		}
		return false;
	}

private:
	/*
	 * Which id will be given to next object.
	 */
	unsigned int id_;

	/*
	 * FIFO of unused objects.
	 */
	std::queue<T*> freeObjects_;

	/*
	 * Used objects.
	 */
	std::map<unsigned int, T*> objects_;
};

#endif /* MANAGER_H_ */
