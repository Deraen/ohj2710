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

void Sprite::reset_inner()
{
	SDL_FreeSurface(surface_);
	surface_ = NULL;
	SDL_DestroyTexture(texture_);
	texture_ = NULL;
}

void Sprite::initialize()
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
	src_.w = 10;
	src_.h = 10;

	// Surface
	SDL_FreeSurface(surface_);
	surface_ = SDL_CreateRGBSurface(0, src_.w, src_.h, 32, rmask, gmask, bmask, amask);

	// #FF00EA
	Uint32 notfound_color = SDL_MapRGB(surface_->format, 255, 0, 240);

	SDL_FillRect(surface_, &src_, notfound_color);

	if (texture_ != NULL) SDL_DestroyTexture(texture_);
	SDL_Log("fuu");
	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
}

void Sprite::draw(Drawable* drawable) const
{
	SDL_Rect dst;
	dst.w = drawable->dimensions().x;
	dst.h = drawable->dimensions().y;
	dst.x = drawable->pos().x;
	dst.y = drawable->pos().y;

	SDL_Renderer* renderer = Screen::instance().renderer();
	SDL_Rect dst_screen = Screen::instance().toScreenCoordinates(dst);

	// NULL = Entire texture
	SDL_RenderCopy(renderer, texture_, NULL, &dst_screen);
}
