#include <algorithm>

#include "DrawableManager.hpp"

void DrawableManager::drawAll()
{
	for (unsigned int i = 0; i < drawables_.size(); ++i) {
		drawables_[i]->draw();
	}
}

unsigned int DrawableManager::newObject()
{
	unsigned int id = Manager::newObject();
	drawables_.push_back(Manager::getObject(id));
	return id;
}

bool DrawableManager::releaseObject(const unsigned int i)
{
	Drawable* obj = Manager::getObject(i);
	auto find = std::find(drawables_.begin(), drawables_.end(), obj);

	if (find != drawables_.end())
	{
		drawables_.erase(find);
	}
	else
	{
		LOGW("Drawable released but could not remove it from draw list, as it wasn't there?");
	}

	return Manager::releaseObject(i);
}