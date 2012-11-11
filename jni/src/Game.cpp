/*
 * Game.cc
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#include "Game.hpp"

#include "objects/Planet.hpp"
#include "objects/Asteroid.hpp"
#include "Screen.hpp"

Game::Game():
	world_(b2Vec2(0.0, 0.0)),
	running_(true)
{
}

Game::~Game()
{
}

void Game::init()
{
	new Planet();
}

void Game::loop()
{
	while(running_)
	{
		Screen::instance().draw();

		Step();

		Screen::instance().processInput();

		// Give other applications some time to execute.
		SDL_Delay(20);
	}
}

void Game::Step()
{
	static const float G = 2.66726;

	world_.Step(1.0 / 60.0, 10, 10);
	world_.ClearForces();

	// All bodies affect all others bodies
	b2Body* body = world_.GetBodyList();
	while (body != NULL)
	{
		b2Body* body2 = world_.GetBodyList();
		while (body2 != NULL)
		{
			if (body != body2)
			{
				b2Vec2 d = body->GetPosition() - body2->GetPosition();
				float f = (G * body->GetMass() * body2->GetMass()) / d.LengthSquared();
				d.Normalize();
				d *= f;

				body2->ApplyForceToCenter(d);
			}
			body2 = body2->GetNext();
		}

		body = body->GetNext();
	}

}
