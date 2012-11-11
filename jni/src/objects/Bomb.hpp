
/*
 * Bomb.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "Box2D/Box2D.h"
#include "Object.hpp"
#include "interfaces/Drawable.hpp"
#include "Assets.hpp"

class Sprite;

class Bomb: public Object, public Drawable
{
public:
	enum BombType {
		NORMAL,
		SPLASH,
		CHAINREACTION
	};

	Bomb(b2Body* planet, float radians, float force);
	virtual ~Bomb();

	inline Sprite* GetSprite() const { return type_.sprite; }
	inline b2Vec2 GetDimensions() const { return type_.meters; }

private:
	b2Body* body_;
	Assets::Type type_;
};

#endif /* BOMB_H_ */
