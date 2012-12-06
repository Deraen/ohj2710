#include <functional>
#include <string>
#include <sstream>

#include "SDL_ttf.h"

#include "UI.hpp"
#include "Screen.hpp"
#include "Game.hpp"

UI::UI():
	buttons_()
{
	unsigned int x = 0;
	unsigned int y = 0;

	x = 9;
	Button* cfg = new Button("Cfg", x, y, 90, 90, 90);
	buttons_.push_back(cfg);

	y += 1;
	Button* debug = new Button("Debug", x, y, 170, 0, 0);
	debug->parent = cfg;
	debug->f = []() {
		Screen::instance().ToggleDebug();
	};
	debug->activef = []() -> bool {
		return Screen::instance().Debug();
	};
	buttons_.push_back(debug);

	x = 0;
	y = 9;
	Button* normal = new Weapon(Bomb::BombType::NORMAL, x, y, 255, 0, 0);
	buttons_.push_back(normal);

	y -= 1;
	Button* splash = new Weapon(Bomb::BombType::SPLASH, x, y, 255, 0, 0);
	buttons_.push_back(splash);

	y -= 1;
	Button* chain = new Weapon(Bomb::BombType::CHAIN, x, y, 255, 0, 0);
	buttons_.push_back(chain);

	y -= 1;
	Button* laser = new Weapon(Bomb::BombType::LASER, x, y, 255, 0, 0);
	buttons_.push_back(laser);

	y = 0;
	Button* points = new Points(x, y, 0, 0, 0);
	buttons_.push_back(points);

	x = 9;
	y = 9;
	Button* levels = new Button("Lvl", x, y, 10, 150, 10);
	levels->f = []() {
		Game::instance().SelectLevel(Game::Levels::COUNT_);
	};
	buttons_.push_back(levels);

	y -= 1;
	Button* lvl1 = new Level(Game::Levels::LVL1, x, y, 10, 150, 10);
	lvl1->parent = levels;
	buttons_.push_back(lvl1);

	y -= 1;
	Button* lvl2 = new Level(Game::Levels::LVL2, x, y, 10, 150, 10);
	lvl2->parent = levels;
	buttons_.push_back(lvl2);

	y -= 1;
	Button* lvl3 = new Level(Game::Levels::LVL3, x, y, 10, 150, 10);
	lvl3->parent = levels;
	buttons_.push_back(lvl3);

	y -= 1;
	Button* inf = new Level(Game::Levels::INF, x, y, 10, 10, 150);
	inf->parent = levels;
	buttons_.push_back(inf);
}

UI::~UI()
{
}

UI::Button::Button(const std::string& text_, unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_):
			text(text_), f(), activef(), parent(NULL), x(x_), y(y_), r(r_), g(g_), b(b_), hover(false), active(false),
			surface_(NULL), texture_(NULL)
{
	SDL_Color color = {255, 255, 255};
	surface_ = TTF_RenderText_Blended(Screen::instance().font(), text.c_str(), color);

	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
}

UI::Weapon::Weapon(Bomb::BombType type_, unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_):
	Button(Bomb::INFO[type_].name, x_, y_, r_, g_, b_),
	type(type_), count(Game::instance().BombCount(type))
{
	f = [&]() {
		Game::instance().SelectWeapon(type);
	};
	activef = [&]() -> bool {
		return Game::instance().SelectedWeapon() == type;
	};
}

UI::Level::Level(Game::Levels level_, unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_):
	Button(Game::LEVELS[level_].name, x_, y_, r_, g_, b_),
	level(level_)
{
	f = [&]() {
		Game::instance().SelectLevel(level);
	};
	activef = [&]() -> bool {
		return Game::instance().SelectedLevel() == level;
	};
}


UI::Points::Points(unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_):
	Button("0", x_, y_, r_, g_, b_),
	points(0)
{
}

void UI::Button::Draw()
{
	if (parent != NULL && !parent->active) return;

	if (activef) active = activef();

	SDL_Rect dst;
	dst.w = Screen::instance().ResX() / 10;
	dst.h = Screen::instance().ResY() / 10;
	dst.x = dst.w * x;
	dst.y = dst.h * y;

	Sint8 a = 120;
	if (hover)
	{
		a = 180;
	}
	else if (active)
	{
		a = 255;
	}
	SDL_SetRenderDrawColor(Screen::instance().renderer(), r, g, b, a);
	SDL_RenderFillRect(Screen::instance().renderer(), &dst);

	dst.x += dst.w * 0.1;
	dst.y += dst.h * 0.1;
	dst.w *= 0.8;
	dst.h *= 0.8;
	SDL_RenderCopy(Screen::instance().renderer(), texture_, NULL, &dst);
}

void UI::Weapon::Draw()
{
	if (Game::instance().BombCount(type) != count)
	{
		SDL_FreeSurface(surface_);
		SDL_DestroyTexture(texture_);

		count = Game::instance().BombCount(type);

		std::ostringstream ss;
		ss << Bomb::INFO[type].name << " " << count;
		text = ss.str();

		SDL_Color color = {255, 255, 255};
		surface_ = TTF_RenderText_Blended(Screen::instance().font(), text.c_str(), color);

		texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
	}
	UI::Button::Draw();
}


void UI::Points::Draw()
{
	if (Game::instance().Points() != points)
	{
		SDL_FreeSurface(surface_);
		SDL_DestroyTexture(texture_);

		points = Game::instance().Points();

		std::ostringstream ss;
		ss << points;
		text = ss.str();

		SDL_Color color = {255, 255, 255};
		surface_ = TTF_RenderText_Blended(Screen::instance().font(), text.c_str(), color);

		texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
	}
	UI::Button::Draw();
}

void UI::Draw() const
{
	SDL_Renderer* renderer = Screen::instance().renderer();
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		buttons_.at(i)->Draw();
	}
}

bool UI::TouchStart(std::pair<unsigned int, unsigned int> p)
{
	unsigned int x = p.first * 10 / Screen::instance().ResX();
	unsigned int y = p.second * 10 / Screen::instance().ResY();

	bool r = false;
	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		if ((buttons_.at(i)->parent == NULL || buttons_.at(i)->parent->active) && buttons_.at(i)->x == x && buttons_.at(i)->y == y)
		{
			buttons_.at(i)->hover = true;
			buttons_.at(i)->active = true;
			r = true;
		}
		else
		{
			buttons_.at(i)->hover = false;
		}
	}

	return r;
}


bool UI::Touch(std::pair<unsigned int, unsigned int> p)
{
	return TouchStart(p);
}

bool UI::TouchEnd()
{
	bool r = false;
	for (unsigned int i = 0; i < buttons_.size(); ++i)
	{
		if (buttons_.at(i)->hover)
		{
			if (buttons_.at(i)->f) buttons_.at(i)->f();
			buttons_.at(i)->hover = false;
			// return;
			r = true;
		}

		buttons_.at(i)->active = false;
	}
	return r;
}
