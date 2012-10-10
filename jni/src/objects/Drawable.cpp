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

void Drawable::initialize(const b2Vec2 &pos, const b2Vec2 &dim)
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
	surface_ = SDL_CreateRGBSurface(0, dim.x, dim.y, 32, rmask, gmask, bmask, amask);

	src_.x = 0;
	src_.y = 0;
	src_.w = dim.x;
	src_.h = dim.y;

	dst_.x = pos.x;
	dst_.y = pos.y;
	dst_.w = dim.x;
	dst_.h = dim.y;

	// #FF00EA
	Uint32 notfound_color = SDL_MapRGB(surface_->format, 255, 0, 240);

	SDL_FillRect(surface_, &src_, notfound_color);

	if (texture_ != NULL) SDL_DestroyTexture(texture_);
	texture_ = SDL_CreateTextureFromSurface(DrawableManager::instance().renderer(), surface_);

	SDL_Log("Drawable %i: %ix%i @ %i,%i", getId(), dst_.w, dst_.h, dst_.x, dst_.y);
}

void Drawable::draw() const
{
	SDL_Renderer* renderer = DrawableManager::instance().renderer();
	SDL_Rect dst_screen = DrawableManager::instance().toScreenCoordinates(dst_);

	// NULL = Entire texture
	SDL_RenderCopy(renderer, texture_, NULL, &dst_screen);
}

void Drawable::updatePos(const b2Vec2 &pos)
{
	dst_.x = pos.x;
	dst_.y = pos.y;
}
