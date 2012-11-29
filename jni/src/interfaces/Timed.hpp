
#ifndef TIMED_HPP_
#define TIMED_HPP_

#include <string>

#include "SDL.h"

class Timed
{
public:
	Timed() {};
	virtual ~Timed() {};

	/*
	 * Callback.
	 */
	virtual void Tick() = 0;
private:
};

#endif /* Timed_HPP_ */
