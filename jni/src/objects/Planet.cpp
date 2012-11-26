/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL_log.h"
#include "SDL2_gfxPrimitives.h"

#include "objects/Planet.hpp"
#include "Game.hpp"
#include "objects/Asteroid.hpp"
#include "Assets.hpp"
#include "objects/Bomb.hpp"
#include "objects/Laser.hpp"
#include "Screen.hpp"

namespace {
	Uint32 SpawnAsteroid(Uint32 interval, void* param)
	{
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::SPAWN_ASTEROID;
		event.user.data1 = param;

		SDL_PushEvent(&event);

		// asteroid every 1ms - 10sec
		return rand() % 9999 + 1;
	}
}

Planet::Planet():
	Object(),
	Drawable(),
	Touchable(),
	weaponAim_(0, 0)
{
	type_ = Assets::instance().info("Planet", "EARTH");

	b2BodyDef temp;
	temp.position = b2Vec2(0.0, 0.0);
	temp.type = b2_staticBody;
	CreateBody(temp, type_.def);

	laser_ = new Laser(GetBody());

	SDL_Log("Planet m=%f", GetMass());

	SDL_AddTimer(10, SpawnAsteroid, GetBody());
}

Planet::~Planet()
{
	SDL_Log("~Planet");
}

void Planet::Draw(b2Body *body) const
{
	if (Game::instance().SelectedWeapon() == Bomb::BombType::LASER)
	{
		laser_->Draw();
	}
	else if (weaponAim_.x != 0 || weaponAim_.y != 0)
	{
		b2Vec2 p1 = Screen::instance().toPixels(GetBody()->GetPosition(), true);
		Sint16 x1 = static_cast<Sint16>(p1.x);
		Sint16 y1 = static_cast<Sint16>(p1.y);

		b2Vec2 p2 = Screen::instance().toPixels(GetBody()->GetPosition() + weaponAim_, true);
		Sint16 x2 = static_cast<Sint16>(p2.x);
		Sint16 y2 = static_cast<Sint16>(p2.y);
		thickLineRGBA(Screen::instance().renderer(), x1, y1, x2, y2, 4, 200, 0, 150, 255);
	}

	Drawable::Draw(body);
}

void Planet::TouchStart()
{
	// touched_ = true;
	if (Game::instance().SelectedWeapon() == Bomb::BombType::LASER)
	{
		laser_->Activate();
	}
}

void Planet::TouchMovement(const b2Vec2 &p)
{
	weaponAim_ = - p - GetBody()->GetPosition();
	if (Game::instance().SelectedWeapon() == Bomb::BombType::LASER)
	{
		laser_->SetAim(weaponAim_);
	}
}

void Planet::TouchEnd()
{
	// touched_ = false;
	if (Game::instance().SelectedWeapon() == Bomb::BombType::LASER)
	{
		laser_->Deactivate();
	}
	else if (Game::instance().WeaponHasUses())
	{

		float force = weaponAim_.Length();
		weaponAim_.Normalize();
		float radians = atan2(weaponAim_.y, weaponAim_.x);

		new Bomb(GetBody(), Game::instance().SelectedWeapon(), radians, force);
		Game::instance().UseWeapon();
	}
	weaponAim_ = b2Vec2(0, 0);
}
