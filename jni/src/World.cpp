/*
 * World.cc
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#include "World.hpp"
#include "managers/DrawableManager.hpp"
#include "managers/AsteroidManager.hpp"
#include "managers/PlayerManager.hpp"

World::World() : world_(b2Vec2(0.0f,0.0f)){
	DrawableManager::instance().init();

	unsigned int player1 = PlayerManager::instance().newObject();
	unsigned int planet1 = 0;
	PlayerManager::instance().withObject(player1, [&](Player* obj)
	{
		obj->initialize("Pelaaja 1");
		planet1 = obj->getPlanet();

		b2BodyDef temp;
		temp.userData = obj;
		temp.position = b2Vec2(0.0f, 0.0f);
		temp.type = b2_staticBody;
		b2Body* body = world_.CreateBody(&temp);

		b2CircleShape circle;

		circle.m_radius = 40.0f;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution = 0.1f;

		body->CreateFixture(&fixtureDef);
		body->ApplyForce(b2Vec2(400.0f,0.0f), body->GetWorldCenter());
		//obj->SetBody(body);
	});

	for (unsigned int i = 0; i < 8; ++i)
	{
		unsigned int asteroid = AsteroidManager::instance().newObject();
		AsteroidManager::instance().withObject(asteroid, [&](Asteroid* obj)
		{
			obj->initialize(planet1);

			b2BodyDef temp;
			temp.userData = obj;
			temp.position = obj->Position();
			temp.type = b2_dynamicBody;
			b2Body* body = world_.CreateBody(&temp);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(5.0f, 5.0f);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 1.0f;
			fixtureDef.restitution = 0.1f;

			body->CreateFixture(&fixtureDef);
			body->ApplyForce(b2Vec2(4000.0f,0.0f), body->GetWorldCenter());
			obj->SetBody(body);
			SDL_Log("(%f, %f)", obj->Position().x, obj->Position().y);
		});
	}

}

World::~World() {

}

void World::Step()
{
	world_.Step(1.0f/30.0f, 10, 10);
	world_.ClearForces();
	AsteroidManager::instance().withObjects([](Asteroid* obj)
	{
		obj->move();
	});
}
