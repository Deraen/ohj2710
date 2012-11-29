/*
 * Sprite.cpp
 */

#include "objects/Sprite.hpp"
#include "Screen.hpp"
#include "interfaces/Drawable.hpp"

namespace
{
	// Pirtää yhden pikselin.
	// Voidaan tarvita vielä, esim. boundingboxien debuggaukseen.
	void plot(SDL_Surface* surface, unsigned int x, unsigned int y, Uint32 color)
	{
		Uint8* buf = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
		*(Uint32*)buf = color;
	}
}

Sprite::Sprite(int x, int y, unsigned char* data):
	surface_(NULL),
	texture_(NULL)
{
	src_.x = 0;
	src_.y = 0;
	src_.w = x;
	src_.h = y;

	// Surface
	surface_ = Screen::CreateSurfaceFrom(data, src_.w, src_.h, 32, src_.w * 4);
	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
}

Sprite::~Sprite()
{
}

void Sprite::Draw(b2Body* body, const b2Vec2& dimensions) const
{
	b2Vec2 dim = Screen::instance().toPixels(dimensions);
	b2Vec2 pos = Screen::instance().toPixels(body->GetPosition(), true);
	double angle = 180.0 / M_PI * body->GetAngle();

	SDL_Rect dst;
	dst.w = dim.x;
	dst.h = dim.y;
	dst.x = pos.x - dim.x / 2;
	dst.y = pos.y - dim.x / 2;

	SDL_Renderer* renderer = Screen::instance().renderer();

	// 3th: NULL = Entire texture
	// 6th: NULL = rotate around center
	SDL_RenderCopyEx(renderer, texture_, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}
