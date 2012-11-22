#include <functional>
#include <string>

#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"

#include "UI.hpp"
#include "Screen.hpp"
#include "Game.hpp"

UI::UI():
	activeMenu_(NULL),
	activeButton_(NULL)
{
	Button* tmp = new Button("Debug", 170, 0, 0);
	tmp->f = []() {
		Screen::instance().toggleDebug();
	};

	menus_[0] = new Menu("Cfg", 90, 90, 90);
	menus_[0]->first = tmp;

	menus_[1] = new Menu("Lvl", 0, 170, 0);

	menus_[2] = new Menu("Wpn", 255, 0, 0);

	tmp = new Button("Normal", 255, 0, 0);
	tmp->f = []() {
		Game::instance().SelectWeapon(Bomb::BombType::NORMAL);
	};
	menus_[2]->first = tmp;

	tmp = new Button("Splash", 255, 0, 0);
	tmp->f = []() {
		Game::instance().SelectWeapon(Bomb::BombType::SPLASH);
	};
	menus_[2]->first->next = tmp;

	tmp = new Button("Chain", 255, 0, 0);
	tmp->f = []() {
		Game::instance().SelectWeapon(Bomb::BombType::CHAIN);
	};
	menus_[2]->first->next->next = tmp;

	tmp = new Button("Laser", 255, 0, 0);
	tmp->f = []() {
		Game::instance().SelectWeapon(Bomb::BombType::LASER);
	};
	menus_[2]->first->next->next->next = tmp;

	menus_[3] = new Menu("Gld", 170, 170, 0);
}

UI::~UI()
{
}

UI::Button::Button(const std::string& text_, Uint8 r_, Uint8 g_, Uint8 b_):
			text(text_), next(NULL), r(r_), g(g_), b(b_), active(false),
			surface_(NULL), texture_(NULL)
{
	SDL_Color color = {255, 255, 255};
	surface_ = TTF_RenderText_Blended(Screen::instance().font(), text.c_str(), color);

	texture_ = SDL_CreateTextureFromSurface(Screen::instance().renderer(), surface_);
}

void UI::Button::Draw(const SDL_Rect& dst) const
{
	Sint8 a = 120;
	if (active) {
		a = 180;
	}
	SDL_SetRenderDrawColor(Screen::instance().renderer(), r, g, b, a);
	SDL_RenderFillRect(Screen::instance().renderer(), &dst);

	SDL_Rect dst_ = dst;
	dst_.x += dst_.w * 0.1;
	dst_.y += dst_.h * 0.1;
	dst_.w *= 0.8;
	dst_.h *= 0.8;
	SDL_RenderCopy(Screen::instance().renderer(), texture_, NULL, &dst_);
}

UI::Menu::Menu(const std::string& text_, Uint8 r_, Uint8 g_, Uint8 b_):
			Button(text_, r_, g_, b_),
			first(NULL)
{
}

void UI::Draw() const
{
	SDL_Renderer* renderer = Screen::instance().renderer();
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Rect dst;
	dst.w = Screen::instance().ResX() / 10;
	dst.h = Screen::instance().ResY() / 10;
	for (unsigned int i = 0; i < 4; ++i)
	{
		Menu* menu = menus_[i];

		// 0  1
		// 2  3
		dst.x = 0;
		dst.y = 0;
		if (i == 1 || i == 3)
		{
			dst.x = Screen::instance().ResX() - dst.w;
		}

		if (i == 2 || i == 3)
		{
			dst.y = Screen::instance().ResY() - dst.h;
		}

		menu->Draw(dst);

		if (menu->active)
		{
			Button* button = menu->first;
			SDL_Rect dst2 = dst;

			while (button != NULL)
			{
				if (i == 0 || i == 1)
				{
					dst2.y += dst.h + 1;
				}
				else
				{
					dst2.y -= dst.h - 1;
				}
				button->Draw(dst2);

				button = button->next;
			}
		}
	}
}

void UI::TouchStart(std::pair<unsigned int, unsigned int> p)
{
	SDL_Rect dst;
	dst.w = Screen::instance().ResX() / 10;
	dst.h = Screen::instance().ResY() / 10;
	for (unsigned int i = 0; i < 4; ++i)
	{
		Menu* menu = menus_[i];

		// 0  1
		// 2  3
		dst.x = 0;
		dst.y = 0;
		if (i == 1 || i == 3)
		{
			dst.x = Screen::instance().ResX() - dst.w;
		}

		if (i == 2 || i == 3)
		{
			dst.y = Screen::instance().ResY() - dst.h;
		}

		if (dst.x <= p.first && p.first <= dst.x + dst.w
		 && dst.y <= p.second && p.second <= dst.y + dst.h)
		{
			if (activeMenu_ != NULL)
			{
				activeMenu_->active = false;
				activeMenu_ = NULL;
			}

			menu->active = true;
			activeMenu_ = menu;
			return;
		}
	}
}


void UI::Touch(std::pair<unsigned int, unsigned int> p)
{
	SDL_Rect dst;
	dst.w = Screen::instance().ResX() / 10;
	dst.h = Screen::instance().ResY() / 10;
	for (unsigned int i = 0; i < 4; ++i)
	{
		Menu* menu = menus_[i];

		// 0  1
		// 2  3
		dst.x = 0;
		dst.y = 0;
		if (i == 1 || i == 3)
		{
			dst.x = Screen::instance().ResX() - dst.w;
		}

		if (i == 2 || i == 3)
		{
			dst.y = Screen::instance().ResY() - dst.h;
		}

		if (menu->active)
		{
			Button* button = menu->first;
			SDL_Rect dst2 = dst;

			while (button != NULL)
			{
				if (i == 0 || i == 1)
				{
					dst2.y += dst.h + 1;
				}
				else
				{
					dst2.y -= dst.h - 1;
				}

				if (dst2.x <= p.first && p.first <= dst2.x + dst2.w
				 && dst2.y <= p.second && p.second <= dst2.y + dst2.h)
				{
					activeButton_ = button;
					activeButton_->active = true;
				}

				button = button->next;
			}
		}
	}
}

void UI::TouchEnd()
{
	if (activeButton_ != NULL)
	{
		activeButton_->f();
		activeButton_->active = false;
		activeButton_ = NULL;
	}

	if (activeMenu_ != NULL)
	{
		activeMenu_->active = false;
		activeMenu_ = NULL;
	}
}
