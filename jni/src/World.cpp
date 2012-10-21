/*
 * World.cc
 *
 *  Created on: 18.10.2012
 *      Author: aijo
 */

#include "World.hpp"
#include "Manager.hpp"

#include "objects/Planet.hpp"
#include "objects/Asteroid.hpp"

World::World() : world_(b2Vec2(0.0f,0.0f)){
	unsigned int planet1 = Manager::instance().newObject<Planet>();

	b2BodyDef temp;
	// temp.userData = obj;
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

	for (unsigned int i = 0; i < 8; ++i)
	{
		unsigned int asteroid = Manager::instance().newObject<Asteroid>();
		Manager::instance().withObject<Asteroid>(asteroid, [&](Asteroid* obj)
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
	Manager::instance().withObjects<Asteroid>([](Asteroid* obj)
	{
		obj->move();
	});
}
