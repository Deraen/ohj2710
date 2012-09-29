/*
 * DrawableManager.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef DRAWABLEMANAGER_HPP_
#define DRAWABLEMANAGER_HPP_

#include "../Manager.hpp"
#include "../objects/Drawable.hpp"

class DrawableManager: public Manager<Drawable> {
public:
	DrawableManager():
		Manager(100)
	{
	}

	virtual ~DrawableManager()
	{
	}

	static DrawableManager& instance()
	{
		static DrawableManager instance_;
		return instance_;
	}

	void drawAll();

	unsigned int newObject();

	bool releaseObject(const unsigned int i);

private:
	std::vector<Drawable*> drawables_;
};

#endif /* DRAWABLEMANAGER_HPP_ */
