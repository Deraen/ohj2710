/*
 * Game.cc
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#include "Game.hpp"

#include "objects/Planet.hpp"
#include "objects/Asteroid.hpp"
 #include "objects/Bomb.hpp"
#include "Screen.hpp"

Game::Game():
	world_(b2Vec2(0.0, 0.0)),
	running_(true),
	toDestroy_()
{
}

Game::~Game()
{
}

void Game::init()
{
	world_.SetContactListener(this);
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

	while (!toDestroy_.empty())
	{
		b2Body* body = toDestroy_.front();
		Object* obj = (Object*) body->GetUserData();
		if (obj != NULL)
		{
			delete obj;
		}
		body->SetUserData(NULL);
		world_.DestroyBody(body);
		toDestroy_.pop();
	}

	// while (!jointsToCreate_.empty())
	// {
	// 	world_.CreateJoint(&jointsToCreate_.front());
	// 	jointsToCreate_.pop();
	// }

	// All bodies affect all others bodies
	b2Body* body = world_.GetBodyList();
	while (body != NULL)
	{
		Object* obj = (Object*)body->GetUserData();
		float m1 = obj->GetMass();

		b2Body* body2 = world_.GetBodyList();
		while (body2 != NULL)
		{
			Object* obj2 = (Object*)body2->GetUserData();

			if (body2->GetType() != b2_staticBody && body != body2)
			{
				b2Vec2 d = body->GetPosition() - body2->GetPosition();
				float m2 = obj2->GetMass();
				float f = (G * m1 * m2) / d.LengthSquared();
				d.Normalize();
				d *= f;

				body2->ApplyForceToCenter(d);
			}
			body2 = body2->GetNext();
		}

		body = body->GetNext();
	}

}

void Game::AsteroidAndBomb(Asteroid *asteroid, Bomb *bomb)
{
	toDestroy_.push(asteroid->GetBody());
	toDestroy_.push(bomb->GetBody());
}

void Game::BeginContact(b2Contact *contact)
{
	Object* obj1 = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
	Object* obj2 = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();

	// Planet is static, it won't collide with others
	if (dynamic_cast<Asteroid*>(obj1) != NULL && dynamic_cast<Planet*>(obj2)) {
		SDL_Log("Contact: Asteroid <-> Planet");
		toDestroy_.push(contact->GetFixtureA()->GetBody());
	} else if (dynamic_cast<Bomb*>(obj1) != NULL && dynamic_cast<Planet*>(obj2)) {
		SDL_Log("Contact: Bomb <-> Planet");
		toDestroy_.push(contact->GetFixtureA()->GetBody());
	} else if ((dynamic_cast<Asteroid*>(obj1) != NULL && dynamic_cast<Bomb*>(obj2))
	        || (dynamic_cast<Bomb*>(obj1) != NULL && dynamic_cast<Asteroid*>(obj2))) {
		SDL_Log("Contact: Asteroid <-> Bomb");
		AsteroidAndBomb((Asteroid*)obj1, (Bomb*)obj2);
	} else if (dynamic_cast<Bomb*>(obj1) != NULL && dynamic_cast<Bomb*>(obj2)) {
		SDL_Log("Conact: Bomb <-> Bomb");
		toDestroy_.push(contact->GetFixtureA()->GetBody());
		toDestroy_.push(contact->GetFixtureB()->GetBody());
	} else if (dynamic_cast<Asteroid*>(obj1) != NULL && dynamic_cast<Asteroid*>(obj2)) {
		// SDL_Log("Contact: Asteroid <-> Asteroid");
		// b2JointDef def;
		// def.bodyA = contact->GetFixtureA()->GetBody();
		// def.bodyB = contact->GetFixtureB()->GetBody();
		// def.type = b2JointType::e_weldJoint;
		// jointsToCreate_.push(def);
		// Instead we should have multiple fixtures of one body for breakable structures
	}
}

// void Game::EndContact(b2Contact *contact)
// {
// 	SDL_Log("Kosketus loppu");
// }
