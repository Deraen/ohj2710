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

Sprite::Sprite():
	surface_(NULL),
	texture_(NULL)
{
}

Sprite::~Sprite()
{
}

void Sprite::initialize(int x, int y, unsigned char* data)
{
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

	src_.x = 0;
	src_.y = 0;
	// XXX: Dimensions of source image
	src_.w = x;
	src_.h = y;

	// Surface
	surface_ = SDL_CreateRGBSurfaceFrom(data, src_.w, src_.h, 32, src_.w * 4, rmask, gmask, bmask, amask);

	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
}

void Sprite::draw(b2Body* body) const
{
	Drawable* drawable = (Drawable*)body->GetUserData();
	b2Vec2 dim = Screen::instance().toPixels(drawable->dimensions());
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
