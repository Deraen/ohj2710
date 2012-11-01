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
	world_.Step(1.0 / 30.0, 10, 10);
	world_.ClearForces();

	b2Body* body = world_.GetBodyList();
	while (body != NULL)
	{
		Asteroid* obj = dynamic_cast<Asteroid*>((Object*)body->GetUserData());
		if (obj != NULL)
		{
			obj->move();
		}

		body = body->GetNext();
	}

}
