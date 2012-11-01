#include "Object.hpp"

#include "objects/Sprite.hpp"

std::map<std::string, Object::TypeInfo> Object::types_;

void Object::addType(const std::string& id, b2Shape* shape, Sprite* sprite, const b2Vec2 &size)
{
	TypeInfo info;
	info.shape = shape;
	info.sprite = sprite;
	info.screenSizeMeters = size;
	types_[id] = info;
}

b2FixtureDef Object::fixtureDef(const std::string& id)
{
	auto f = types_.find(id);
	b2FixtureDef def;

	if (f != types_.end())
	{
		TypeInfo type = f->second;

		def.shape = type.shape;
		def.density = 1.0;
		def.friction = 1.0;
		def.restitution = 0.1;
	}
	return def;
}

Sprite* Object::sprite(const std::string& id)
{
	auto f = types_.find(id);
	if (f != types_.end()) {
		return f->second.sprite;
	}
	return NULL;
}
