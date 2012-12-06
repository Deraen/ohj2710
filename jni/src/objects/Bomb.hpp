
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
#include "interfaces/Timed.hpp"
#include "Assets.hpp"

class Sprite;

class Bomb: public Object, public Drawable, public Timed
{
public:
	enum BombType {
		NORMAL,
		SPLASH,
		CHAIN,
		LASER,
		COUNT_
	};
	struct Info {
		std::string name;
		int quota;
		unsigned int replenishTime;
	};
	static const Info INFO[];

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

	void Tick();

private:
	void init(const b2Vec2& pos);

	Assets::Type type_;
	BombType type__;
	Status status_;

	static unsigned int count_;

	Uint32 previous_;
};

#endif /* BOMB_H_ */
