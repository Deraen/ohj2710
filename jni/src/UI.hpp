#ifndef UI_HPP_
#define UI_HPP_

#include <functional>
#include <string>

#include "SDL2_gfxPrimitives.h"

class UI
{
public:
	UI();
	virtual ~UI();

	void Draw() const;

	void Touch(std::pair<unsigned int, unsigned int> p);
	void TouchEnd();
private:
	struct Button
	{
		Button(const std::string& text_, Uint8 r_, Uint8 g_, Uint8 b_);

		const std::string text;
		std::function<void()> f;
		Button* next;
		Uint8 r;
		Uint8 g;
		Uint8 b;
		bool active;

		void Draw(const SDL_Rect& dst) const;

		SDL_Surface* surface_;
		SDL_Texture* texture_;
	};

	struct Menu: public Button
	{
		Menu(const std::string& text_, Uint8 r_, Uint8 g_, Uint8 b_);

		Button* first;
	};

	Menu* menus_[4];
	Menu* activeMenu_;
	Button* activeButton_;
};

#endif
