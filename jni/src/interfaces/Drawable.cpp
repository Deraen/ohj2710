#include "interfaces/Drawable.hpp"
#include "objects/Sprite.hpp"

void Drawable::Draw(b2Body* body) const
{
	GetSprite()->Draw(body, GetDimensions());
}
