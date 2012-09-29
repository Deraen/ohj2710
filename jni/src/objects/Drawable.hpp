/*
 * Drawable.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: juho
 */

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "../Object.hpp"

class Drawable: public Object {
public:
	enum DrawableType {
		CIRCLE,
		TRIANGLE,
		SPRITE,
	};

	Drawable();
	virtual ~Drawable();

	void reset_inner();

	void initialize(DrawableType type);

	void circle(float r);

	void draw() const;
private:
	DrawableType type_;

	float r_;
};

#endif /* Drawable_HPP_ */
