/*
 * Asteroid.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: juho
 */

#include <cstdlib>
#include <cmath>

#include "Asteroid.hpp"
#include "managers/DrawableManager.hpp"
#include "managers/PlanetManager.hpp"

Asteroid::Asteroid() {
	// TODO Auto-generated constructor stub

}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::reset_inner()
{

}

void Asteroid::initialize(const unsigned int planet)
{
	planet_ = planet;

	// Random number between 0 and 2*PI
	float pos = (rand() % 2000) * M_PI / 1000.0;

	// Init pos
	pos_.x = 200.0f * std::cos(pos);
	pos_.y = 200.0f * std::sin(pos);

	drawable_ = DrawableManager::instance().newObject();
	DrawableManager::instance().withObject(drawable_, [this](Drawable* obj)
	{
		obj->initialize(pos_, b2Vec2(10, 10));
	});

}

#define SCALE(OldValue, OldMin, OldMax, NewMin, NewMax) ((((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin);

void Asteroid::move()
{
	float planetRadius = 40.0f;
	b2Vec2 planetPos(0.0f, 0.0f);
	b2Vec2 asteroidPos = body_->GetPosition();
	float asteroidDistance = asteroidPos.Length();
	//SDL_Log("(%f)", asteroidDistance);

	if (asteroidDistance < 6.0f * planetRadius)
	{
		b2Vec2 superForce(0.0f, 0.0f);
		asteroidPos *= -1.0f;
		float vecSum = abs(asteroidPos.x) + abs(asteroidPos.y);
		asteroidPos *= (1.0/vecSum) * (40.0f / asteroidDistance);

		b2Vec2 F(asteroidPos.x * 10.0f, asteroidPos.y * 10.0f);
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
		body_->ApplyForce(4000.0f * superForce, body_->GetWorldCenter());

		velocity_ = body_->GetLinearVelocity();
		pos_ = body_->GetPosition();
	}

	/*b2Vec2 verschil = velocity_ - body_->GetLinearVelocity();

	double forceMultiplier = body_->GetLinearVelocity().Length() * (verschil * 2.0);
	b2Vec2 newForce()
	pos_ = body_->GetPosition();*/
	//SDL_Log("(%f, %f)", pos_.x, pos_.y);
	//body_->ApplyForce(b2Vec2(4,2), body_->GetWorldCenter());
	//body_->SetLinearDamping(10.0f);
	//pos_= body_->GetPosition();
	//SDL_Log("(%f, %f)", pos_.x, pos_.y);
	DrawableManager::instance().withObject(drawable_, [this](Drawable* obj)
	{
		obj->updatePos(pos_);
	});
}
