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

template<typename T>
class Manager
{
public:
	/*
	 * precreate: Define how many objects will be created when manager is initialized.
	 */
	Manager(const unsigned int precreate):
		id_(0)
	{
		for (unsigned int i = 0; i < precreate; ++i)
		{
			freeObjects_.push(createObject());
		}
	}
	virtual ~Manager() {};

	/*
	 * Reserves object and returns id which can be used to access object.
	 *
	 * Id 0 is not used, first object gets id 1.
	 */
	virtual unsigned int newObject()
	{
		id_++;

		if (!freeObjects_.empty())
		{
			if (freeObjects_.front()->getId() != 0) {
				SDL_Log("Using object (%i) as a free object but it hasn't been freed.",
				        freeObjects_.front()->getId());
			}

			objects_[id_] = freeObjects_.front();
			freeObjects_.pop();
		}
		else
		{
			objects_[id_] = createObject();
		}
		objects_[id_]->setId(id_);
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
	void withObject(const unsigned int i, std::function<void(T*)> f) const
	{
		auto find = objects_.find(i);

		if (find != objects_.end())
		{
			f(find->second);
		}
	}

	/*
	 * Do something with all of objects.
	 */
	void withObjects(std::function<void(T*)> f) const
	{
		for (auto i = objects_.begin(); i != objects_.end(); ++i)
		{
			f(i->second);
		}
	}

	/*
	 * Releases object by id.
	 * Released objects are not destroyed but reseted and put back into queue for unused objects.
	 */
	virtual bool releaseObject(const unsigned int i)
	{
		auto find = objects_.find(i);

		if (find != objects_.end())
		{
			T* obj = find->second;
			objects_.erase(find);

			obj->reset();
			freeObjects_.push(obj);
			return true;
		}
		return false;
	}

private:
	/*
	 * Used objects.
	 */
	std::map<unsigned int, T*> objects_;

	/*
	 * Which id will be given to next object.
	 */
	unsigned int id_;

	/*
	 * FIFO of unused objects.
	 */
	std::queue<T*> freeObjects_;


	/*
	 * Shortcut to create new Objects.
	 * obj->reset has to be called always as constructors do nothing.
	 */
	T* createObject()
	{
		T* obj = new T;
		obj->reset();
		return obj;
	}
};

#endif /* MANAGER_H_ */
