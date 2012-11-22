
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
		CHAIN,
		LASER
	};
	static const std::string TYPENAMES[];

	enum Status {
		DETONATED,
		DEFAULT
	};

	Bomb(b2Body* planet, BombType type, float radians, float force);
	Bomb(BombType type, b2Vec2 pos, Status status);
	virtual ~Bomb();

	void Draw(b2Body* body) const;

	inline Sprite* GetSprite() const { return type_.sprite; }
	inline b2Vec2 GetDimensions() const { return type_.meters; }

	// starts explosion
	void Detonate(b2Body* other);

	float GetMass() const;

private:
	Assets::Type type_;
	BombType type__;
	Status status_;

	static unsigned int count_;
};

#endif /* BOMB_H_ */
