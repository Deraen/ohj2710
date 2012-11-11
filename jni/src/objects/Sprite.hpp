/*
 * Sprite.hpp
 */

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "SDL.h"
#include "Box2D/Box2D.h"

class Sprite
{
public:
	Sprite(int x, int y, unsigned char* data);
	virtual ~Sprite();

	void Draw(b2Body* body, const b2Vec2& dimensions) const;

private:
	SDL_Surface* surface_;
	SDL_Texture* texture_;

	/*
	 * Size of sprite.
	 */
	SDL_Rect src_;
};

#endif /* SPRITE_HPP_ */
