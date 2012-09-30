/*
 * Drawable.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#include "Drawable.hpp"
#include "../managers/DrawableManager.hpp"

namespace {
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

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

void Drawable::reset_inner()
{
	SDL_FreeSurface(surface_);
	surface_ = NULL;
	SDL_DestroyTexture(texture_);
	texture_ = NULL;
}

void Drawable::initialize(DrawableType type, int x, int y, unsigned int w, unsigned int h)
{
	type_ = type;

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
}

void Drawable::circle(float r)
{
	r_ = r;
	Uint32 color = SDL_MapRGB(surface_->format, 230, 230, 230);

	// Lets draw circle to surface.
	int cx = src_.w / 2;
	int cy = src_.h / 2;

	SDL_LockSurface(surface_);

	int u, v; bool diagonal = false;
	for (u = static_cast<int>(r), v = 0; u > v;) { // start from a know pixel (u,v)=(r,0) on the x axis, compute only the first octant (u > v)
		plot(surface_, cx + u, cy + v, color); plot(surface_, cx + v, cy + u, color);
		plot(surface_, cx - u, cy + v, color); plot(surface_, cx - v, cy + u, color);
		plot(surface_, cx + u, cy - v, color); plot(surface_, cx + v, cy - u, color);
		plot(surface_, cx - u, cy - v, color); plot(surface_, cx - v, cy - u, color);
		v++; // next pixel is above (in the first octant)
		// if the pixel above is at distance greater than 1/2+r from the origin
		// we could test if (v^2 + u^2 >= (1/2+r)^2), but the following is equivalent with integers: 
		if ((diagonal = v*v + u*u - (1 + r)*r > 0))
			u--; // choose the diagonal pixel instead (to the right in the first octant)
	}

	if (u == v && diagonal) { // last pixel if it's on the 45° diagonal
		plot(surface_, cx + u, cy + u, color);
		plot(surface_, cx - u, cy + u, color);
		plot(surface_, cx + u, cy - u, color);
		plot(surface_, cx - u, cy - u, color);
	}

	SDL_UnlockSurface(surface_);

	// Create texture from surface for easy drawing later.
	if (texture_ != NULL) SDL_DestroyTexture(texture_);
	texture_ = SDL_CreateTextureFromSurface(DrawableManager::instance().renderer(), surface_);
}

void Drawable::draw() const
{
	SDL_Renderer* renderer = DrawableManager::instance().renderer();

	if (type_ == CIRCLE)
	{
		SDL_RenderCopy(renderer, texture_, &src_, &dst_);
	}
}
