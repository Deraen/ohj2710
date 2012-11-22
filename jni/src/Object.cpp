#include "Object.hpp"
#include "Game.hpp"

void Object::CreateBody(b2BodyDef &def, b2FixtureDef *def2)
{
	def.userData = this;
	body_ = Game::instance().world()->CreateBody(&def);
	body_->CreateFixture(def2);
}
