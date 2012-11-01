/*
 * Asteroid.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include <cstdlib>
#include <cmath>

#include "objects/Asteroid.hpp"
#include "Game.hpp"
#include "objects/Planet.hpp"
#include "Assets.hpp"

Asteroid::Asteroid(b2Body* planet):
	Object(),
	Drawable()
{
	sprite_ = Object::sprite("asteroid");

	// Random number between 0 and 2*PI
	float pos = (rand() % 2000) * M_PI / 1000.0;

	// Init Box2D
	b2BodyDef temp;
	temp.userData = this;
	temp.position = planet->GetPosition() + b2Vec2(5.0f * std::cos(pos), 5.0f * std::sin(pos));
	temp.type = b2_dynamicBody;
	body_ = Game::instance().world()->CreateBody(&temp);

	b2FixtureDef def = Object::fixtureDef("asteroid");

	body_->CreateFixture(&def);
	body_->ApplyForce(b2Vec2(1.5f, 0.0f), body_->GetWorldCenter());
	SDL_Log("Asteroid created (%f, %f)", body_->GetPosition().x, body_->GetPosition().y);
}

Asteroid::~Asteroid()
{
}

void Asteroid::move()
{
	b2Vec2 asteroidPos = body_->GetPosition();
	float asteroidDistance = asteroidPos.LengthSquared();

	if (asteroidDistance < 10 * Planet::RADIUS * Planet::RADIUS)
	{
		b2Vec2 superForce(0.0f, 0.0f);
		asteroidPos *= -1.0f;
		float vecSum = abs(asteroidPos.x) + abs(asteroidPos.y);
		asteroidPos *= (1.0 / vecSum) * (4.0f / asteroidDistance);

		b2Vec2 F(asteroidPos);
		F *= 0.5;
		superForce += F;

		/*for(int i = 1; i <= asteroidDistance; ++i)
		{
			float speedD = body_->GetLinearVelocity().Length();
			b2Vec2 extraForce((asteroidPos.x * speedD)/ pow(float(i), 2.0f),
					(asteroidPos.y * speedD)/ (float(i), 2.0f));
			superForce += extraForce;

			float mm = SCALE(speedD, 0.0f, 45.0f, 2.0f, 3.0f);
			float dampValue = (0.0314f * speedD) / mm;
			//body_->SetLinearDamping(dampValue);
		}

		if (velocity_.Length() > body_->GetLinearVelocity().Length())
		{
			float verschil2 = velocity_.Length() - body_->GetLinearVelocity().Length();

			float forceMultiplier = body_->GetLinearVelocity().Length() * (verschil2 * 2.0f);
			b2Vec2 newF = forceMultiplier * F;

			float diffDistance = pos_.Length() - asteroidDistance;

			if (diffDistance > 0.0f)
			{
				superForce += newF;
			}

			float speedD = body_->GetLinearVelocity().Length();
			float mm2 = SCALE(speedD, 0.0f, 45.0f, 2.0f, 3.0f);

			float dampValue2 = (0.0314f * speedD) / mm2;
			//body_->SetLinearDamping(dampValue2 * 2.0f);
		}*/

		//SDL_Log("(%f, %f)", superForce.x, superForce.y);

		//superForce *= 1000.0f;
		body_->ApplyForce(superForce, body_->GetWorldCenter());
	}

	/*b2Vec2 verschil = velocity_ - body_->GetLinearVelocity();

	double forceMultiplier = body_->GetLinearVelocity().Length() * (verschil * 2.0);
	b2Vec2 newForce()
	pos_ = body_->GetPosition();*/
	//SDL_Log("(%f, %f)", pos_.x, pos_.y);
	//body_->ApplyForce(b2Vec2(4,2), body_->GetWorldCenter());
	//body_->SetLinearDamping(10.0f);
	//pos_= body_->GetPosition();
	// SDL_Log("Asteroid moved (%f, %f)", body_->GetPosition().x, body_->GetPosition().y);
}
