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
	aim_(0, 0)
{
	// type_ = Assets::instance().info("Laser", INFO[type].name);

	Planet* planet = (Planet*)parent->GetUserData();
	float r = planet->GetRadius() + 1.0;

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

	Uint32 color = SDL_MapRGBA(surface->format, 0, 250, 0, 255);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1;
	rect.h = 1;
	SDL_FillRect(surface, &rect, color);

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

	unsigned int px = Screen::instance().pixelsPerMeter();
	b2Vec2 p1 = Screen::instance().toPixels(parent_->GetPosition(), true);

	if (Game::instance().SelectedLevel() == Game::Levels::INF)
	{
		p1.x -= 0.5 * px;
		p1.y -= 0.7 * px;
	}

	SDL_Rect dst;
	dst.x = p1.x;
	dst.y = p1.y;
	dst.w = aim_.Length() * Screen::instance().pixelsPerMeter();
	dst.h = 8;

	float32 angle = 180 * atan2(aim_.y, aim_.x) / M_PI;
#ifdef __ANDROID__
		angle = -angle;
#endif
	SDL_RenderCopyEx(Screen::instance().renderer(), texture_, NULL, &dst, angle, &rot, SDL_FLIP_NONE);

	Game::instance().world()->RayCast(this, parent_->GetPosition(), parent_->GetPosition() + aim_);
}

namespace {
	Uint32 UseLaser(Uint32 interval, void* param)
	{
		SDL_Event event;
		// This might be called from a different thread but probably it doesn't matter
		if (!((Laser*)param)->Active() || !Game::instance().WeaponHasUses())
		{
			event.type = SDL_USEREVENT;
			event.user.code = Game::STOP_LASER_FUU;
			event.user.data1 = param;
			interval = 0;
		}
		else
		{
			event.type = SDL_USEREVENT;
			event.user.code = Game::USE_WEAPON;
			interval = 500;
		}

		SDL_PushEvent(&event);

		return interval;
	}
}

void Laser::Activate()
{
	active_ = true;
	SDL_AddTimer(10, UseLaser, this);
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

		Game::instance().addPoint();
	}
	return 1;
}
