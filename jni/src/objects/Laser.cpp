/*
 * Laser.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL.h"

#include "Assets.hpp"
#include "Laser.hpp"
#include "Game.hpp"
#include "interfaces/Drawable.hpp"
#include "objects/Planet.hpp"
#include "objects/Asteroid.hpp"
#include "Screen.hpp"

Laser::Laser(b2Body* parent):
	parent_(parent),
	active_(false),
	aim_(0, 0),
	previous_(SDL_GetTicks())
{
	SDL_Surface* surface = Screen::CreateSurface(1, 1, 32);

	Uint32 color = SDL_MapRGBA(surface->format, 0, 250, 0, 255);
	SDL_FillRect(surface, NULL, color);

	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface);
}

Laser::~Laser()
{
	SDL_Log("~Laser");
}

void Laser::Draw()
{
	static SDL_Point rot;
	rot.x = 0;
	rot.y = 2;

	if (!active_) return;

	b2Vec2 p1 = Screen::instance().toPixels(parent_->GetPosition(), true);

	SDL_Rect dst;
	dst.x = p1.x;
	dst.y = p1.y;
	dst.w = aim_.Length() * Screen::instance().pixelsPerMeter();
	dst.h = 8;

	float32 angle = 180 * atan2(aim_.y, aim_.x) / M_PI;
#ifdef __ANDROID__
	// Wat...
	angle = -angle;
#endif
	SDL_RenderCopyEx(Screen::instance().renderer(), texture_, NULL, &dst, angle, &rot, SDL_FLIP_NONE);

	Game::instance().World()->RayCast(this, parent_->GetPosition(), parent_->GetPosition() + aim_);
}

void Laser::Tick()
{
	if (active_ && SDL_GetTicks() - previous_ > 500)
	{
		if (!Game::instance().WeaponHasUses())
		{
			active_ = false;
		}
		else
		{
			Game::instance().UseWeapon();
		}
		previous_ = SDL_GetTicks();
	}
}

void Laser::Activate()
{
	active_ = true;

	// We want first tick immediately
	previous_ = 0;
}

void Laser::Deactivate()
{
	active_ = false;
}

void Laser::SetAim(const b2Vec2& aim)
{
	aim_ = -aim;
	aim_.Normalize();
	aim_ *= 6;
}

float32 Laser::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>((Object*)fixture->GetBody()->GetUserData());
	if (asteroid != NULL) {
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::DELETE_BODY;
		event.user.data1 = fixture->GetBody();

		SDL_PushEvent(&event);

		Game::instance().AddPoint();
	}
	return 1;
}
