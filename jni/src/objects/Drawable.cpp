/*
 * Drawable.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#include "Drawable.hpp"
#include "managers/DrawableManager.hpp"

namespace
{
	void plot(SDL_Surface* surface, unsigned int x, unsigned int y, Uint32 color)
	{
		Uint8* buf = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
		*(Uint32*)buf = color;
	}
}

Drawable::Drawable():
	surface_(NULL),
	texture_(NULL)
{
	// TODO Auto-generated constructor stub

}

Drawable::~Drawable()
{
	// TODO Auto-generated destructor stub
}

void Drawable::reset_inner()
{
	SDL_FreeSurface(surface_);
	surface_ = NULL;
	SDL_DestroyTexture(texture_);
	texture_ = NULL;
}

void Drawable::initialize(int x, int y, unsigned int w, unsigned int h)
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

	// Surface
	SDL_FreeSurface(surface_);
	surface_ = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);

	src_.x = 0;
	src_.y = 0;
	src_.w = w;
	src_.h = h;

	dst_.x = 800 / 2 - w / 2 + x;
	dst_.y = 480 / 2 - h / 2 + y;
	dst_.w = w;
	dst_.h = h;

	// #FF00EA
	Uint32 notfound_color = SDL_MapRGB(surface_->format, 255, 0, 240);

	SDL_FillRect(surface_, &src_, notfound_color);

	if (texture_ != NULL) SDL_DestroyTexture(texture_);
	texture_ = SDL_CreateTextureFromSurface(DrawableManager::instance().renderer(), surface_);
}

void Drawable::draw() const
{
	SDL_Renderer* renderer = DrawableManager::instance().renderer();

	SDL_RenderCopy(renderer, texture_, &src_, &dst_);
}
