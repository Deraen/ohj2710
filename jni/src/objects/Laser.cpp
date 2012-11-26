/*
 * Laser.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include "SDL2_gfxPrimitives.h"

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
}

Laser::~Laser()
{
	SDL_Log("~Laser");
}

void Laser::Draw()
{
	if (!Game::instance().WeaponHasUses()) {
		active_ = false;
		SDL_RemoveTimer(timer_);
		timer_ = 0;
	}

	if (!active_) return;

	unsigned int px = Screen::instance().pixelsPerMeter();
	b2Vec2 p = Screen::instance().toPixels(parent_->GetPosition(), true);
	Sint16 x1 = p.x;
	Sint16 y1 = p.y;
	Sint16 x2 = p.x + aim_.x * px;
	Sint16 y2 = p.y + aim_.y * px;
	auto render = Screen::instance().renderer();

	thickLineRGBA(render, x1, y1, x2, y2, 10, 200, 0, 0, 255);

	Game::instance().world()->RayCast(this, parent_->GetPosition(), parent_->GetPosition() + aim_);
}

namespace {
	Uint32 UseLaser(Uint32 interval, void* param)
	{
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = Game::USE_WEAPON;

		SDL_PushEvent(&event);

		return 500;
	}
}

void Laser::Activate()
{
	active_ = true;
	timer_ = SDL_AddTimer(10, UseLaser, NULL);
}

void Laser::Deactivate()
{
	active_ = false;
	SDL_RemoveTimer(timer_);
	timer_ = 0;
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
