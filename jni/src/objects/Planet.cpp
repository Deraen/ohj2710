/*
 * Planet.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL.h"

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

		// asteroid every 1ms - 5sec
		return rand() % 4999 + 1;
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

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface* surface = SDL_CreateRGBSurface(0, 1, 1, 32, rmask, gmask, bmask, amask);

	Uint32 color = SDL_MapRGBA(surface->format, 255, 0, 150, 255);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1;
	rect.h = 1;
	SDL_FillRect(surface, &rect, color);

	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface);
}

Planet::~Planet()
{
	SDL_Log("~Planet");
}

void Planet::Draw(b2Body *body) const
{
	static SDL_Point rot;
	rot.x = 0;
	rot.y = 2;
	if (Game::instance().SelectedWeapon() == Bomb::BombType::LASER)
	{
		laser_->Draw();
	}
	else if (weaponAim_.x != 0 || weaponAim_.y != 0)
	{
		b2Vec2 p1 = Screen::instance().toPixels(GetBody()->GetPosition(), true);

		SDL_Rect dst;
		dst.x = p1.x;
		dst.y = p1.y;
		dst.w = weaponAim_.Length() * Screen::instance().pixelsPerMeter();
		dst.h = 5;

		float32 angle = (180 * atan2(weaponAim_.y, weaponAim_.x) / M_PI);
#ifdef __ANDROID__
		// There might be a bug in SDL...
		angle = -angle;
#endif
		SDL_RenderCopyEx(Screen::instance().renderer(), texture_, NULL, &dst, angle, &rot, SDL_FLIP_NONE);
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
