

/*
 * Planet.h
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Box2D/Box2D.h"

#include "Object.hpp"
#include "interfaces/Drawable.hpp"
#include "interfaces/Touchable.hpp"
#include "Assets.hpp"

class Laser;

/*
 * A planet is a player.
 */
class Planet: public Object, public Drawable, public Touchable
{
public:
	Planet(std::string name);
	virtual ~Planet();

	inline float GetRadius() const { return type_.def->shape->m_radius; }
	inline float GetMass() const { return 2 * M_PI * GetRadius() * type_.def->density; }

	void Draw(b2Body* body) const;

	inline Sprite* GetSprite() const { return type_.sprite; }
	inline b2Vec2 GetDimensions() const { return type_.meters; }

	void TouchStart();
	void TouchMovement(const b2Vec2& p);
	void TouchEnd();
private:
	Assets::Type type_;
	Laser* laser_;
	b2Vec2 weaponAim_;

	// For drawing weapon aim
	SDL_Texture* texture_;

	SDL_TimerID timer_;
};

#endif /* PLANET_H_ */
