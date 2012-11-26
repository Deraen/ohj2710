

/*
 * Laser.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef LASER_H_
#define LASER_H_

#include "Box2D/Box2D.h"
#include "Object.hpp"
#include "interfaces/Drawable.hpp"
#include "Assets.hpp"

class Sprite;

class Laser: public b2RayCastCallback
{
public:
	Laser(b2Body* parent);
	virtual ~Laser();

	void Draw();

	inline Sprite* GetSprite() const { return NULL; }
	inline b2Vec2 GetDimensions() const { return b2Vec2(0, 0); }

	void Activate();
	void Deactivate();
	void SetAim(const b2Vec2& aim);

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

private:
	b2Body* parent_;
	bool active_;
	b2Vec2 aim_;
	SDL_TimerID timer_;
};

#endif /* LASER_H_ */
