/*
 * Object.h
 *
 *  Created on: Sep 24, 2012
 *      Author: juho
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <map>
#include "Box2D/Box2D.h"

class Sprite;

class Object
{
public:
	Object() {};
	virtual ~Object() {};

	static void addType(const std::string& id, b2Shape* shape, Sprite* sprite, const b2Vec2& size);

	static b2FixtureDef fixtureDef(const std::string& id);

	static Sprite* sprite(const std::string& id);

	struct TypeInfo {
		b2Shape* shape;
		Sprite* sprite;
		b2Vec2 screenSizeMeters;
	};

private:
	static std::map<std::string, TypeInfo> types_;
};

#endif /* OBJECT_H_ */
