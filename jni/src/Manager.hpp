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
#include <functional>

#include "SDL_log.h"

#include "Object.hpp"

class Manager
{
public:
	/*
	 * precreate: Define how many objects will be created when manager is initialized.
	 */
	Manager();
	virtual ~Manager();

	static Manager& instance();

	/*
	 * Reserves object and returns id which can be used to access object.
	 *
	 * Id 0 is not used, first object gets id 1.
	 */
	template<typename T>
	unsigned int newObject()
	{
		id_++;

		objects_[id_] = new T;
		objects_[id_]->setId(id_);

		SDL_Log("New object %i", id_);

		return id_;
	}

	/*
	 * Do something with object.
	 * If object is not found do nothing.
	 *
	 * Examples:
	 * withObject(1, [](Object* obj) {obj->hello();})
	 *
	 * [this] Capture the this pointer of the enclosing class
	 * withObject(2, [this](Object* obj) {obj->hello(this->value)})
	 *
	 * [&] Capture any referenced variable by reference
	 * withObject(3, [&](Object* obj) {obj->hello(local);})
	 */
	template<typename T>
	void withObject(const unsigned int i, std::function<void(T*)> f) const
	{
		auto find = objects_.find(i);

		if (find != objects_.end())
		{
			T* obj = dynamic_cast<T*>(find->second);
			if (obj != NULL) {
				f(obj);
			}
		}
	}

	/*
	 * Do something with all of objects.
	 */
	template<typename T>
	void withObjects(std::function<void(T*)> f) const
	{
		for (auto i = objects_.begin(); i != objects_.end(); ++i)
		{
			T* obj = dynamic_cast<T*>(i->second);
			if (obj != NULL) {
				f(obj);
			}
		}
	}

	/*
	 * Releases object by id.
	 * Released objects are not destroyed but reseted and put back into queue for unused objects.
	 */
	virtual bool releaseObject(const unsigned int i);

private:
	/*
	 * Used objects.
	 */
	std::map<unsigned int, Object*> objects_;

	/*
	 * Which id will be given to next object.
	 */
	unsigned int id_;
};

#endif /* MANAGER_H_ */
