#ifndef UI_HPP_
#define UI_HPP_

#include <functional>
#include <string>
#include <vector>

#include "objects/Bomb.hpp"
#include "Game.hpp"

class UI
{
public:
	UI();
	virtual ~UI();

	void Draw() const;

	bool TouchStart(std::pair<unsigned int, unsigned int> p);
	bool Touch(std::pair<unsigned int, unsigned int> p);
	bool TouchEnd();
private:
	struct Button
	{
		Button(const std::string& text_, unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_);

		std::string text;
		std::function<void()> f;
		std::function<bool()> activef;
		Button* parent;
		unsigned int x;
		unsigned int y;
		Uint8 r;
		Uint8 g;
		Uint8 b;
		bool active;
		bool hover;

		virtual void Draw();

		SDL_Surface* surface_;
		SDL_Texture* texture_;
	};

	struct Weapon: public Button
	{
		Weapon(Bomb::BombType type_, unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_);

		void Draw();

		Bomb::BombType type;
		unsigned int count;
	};

	struct Level: public Button
	{
		Level(Game::Levels type_, unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_);

		Game::Levels level;
	};

	struct Points: public Button
	{
		Points(unsigned int x_, unsigned int y_, Uint8 r_, Uint8 g_, Uint8 b_);

		void Draw();

		int points;
	};

	std::vector<Button*> buttons_;
};

#endif
