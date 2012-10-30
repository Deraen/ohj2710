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

class Sprite;

class Bomb: public Object, public Drawable
{
public:
	enum BombType {
		NORMAL,
		SPLASH,
		CHAINREACTION
	};

	Bomb(b2Body* planet);
	virtual ~Bomb();

	inline Sprite* sprite() const { return sprite_; }
	inline b2Vec2 dimensions() const { return b2Vec2(0.2, 0.2); }

private:
	b2Body* body_;
	Sprite* sprite_;

	/*
	 *
	 */
	BombType type_;
};

#endif /* BOMB_H_ */
