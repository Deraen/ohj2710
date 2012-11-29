#include "SDL2_gfxPrimitives.h"

#include "DebugDraw.hpp"
#include "Screen.hpp"

DebugDraw::DebugDraw():
	a_(150)
{
}

DebugDraw::~DebugDraw()
{
}

namespace
{
	void Polygon(int(*f)(SDL_Renderer*, const Sint16*, const Sint16*, int, Uint8, Uint8, Uint8, Uint8), const b2Vec2 *vertices, int32 vertexCount, const b2Color &color, const Uint8 a)
	{
		Uint8 r = color.r * 255;
		Uint8 g = color.g * 255;
		Uint8 b = color.b * 255;

		Sint16* vx = new Sint16[vertexCount];
		Sint16* vy = new Sint16[vertexCount];
		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			b2Vec2 pixels = Screen::instance().toPixels(vertices[i], true);
			Sint16 x = static_cast<Sint16>(pixels.x);
			Sint16 y = static_cast<Sint16>(pixels.y);
			vx[i] = x;
			vy[i] = y;
		}

		f(Screen::instance().renderer(), vx, vy, vertexCount, r, g, b, a);
		delete[] vx;
		delete[] vy;
	}

	void Circle(int(*f)(SDL_Renderer*, Sint16, Sint16, Sint16, Uint8, Uint8, Uint8, Uint8), const b2Vec2 &center, float32 radius, const b2Color &color, const Uint8 a)
	{
		Uint8 r = color.r * 255;
		Uint8 g = color.g * 255;
		Uint8 b = color.b * 255;

		b2Vec2 pixels = Screen::instance().toPixels(center, true);

		Sint16 radiusPx = static_cast<Sint16>(radius * Screen::instance().pixelsPerMeter());
		Sint16 x = static_cast<Sint16>(pixels.x);
		Sint16 y = static_cast<Sint16>(pixels.y);

		f(Screen::instance().renderer(), x, y, radiusPx, r, g, b, a);
	}
}

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
	Polygon(polygonRGBA, vertices, vertexCount, color, a_);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
	Polygon(filledPolygonRGBA, vertices, vertexCount, color, a_);
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color)
{
	Circle(circleRGBA, center, radius, color, a_);
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)
{
	Circle(filledCircleRGBA, center, radius, color, a_);
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
	Uint8 r = color.r * 255;
	Uint8 g = color.g * 255;
	Uint8 b = color.b * 255;

	b2Vec2 pixels1 = Screen::instance().toPixels(p1, true);
	b2Vec2 pixels2 = Screen::instance().toPixels(p2, true);

	lineRGBA(Screen::instance().renderer(),
	         static_cast<Sint16>(pixels1.x),
	         static_cast<Sint16>(pixels1.y),
	         static_cast<Sint16>(pixels2.x),
	         static_cast<Sint16>(pixels2.y), r, g, b, a_);
}

void DebugDraw::DrawTransform(const b2Transform &xf)
{
	// Position & Rotation
}
