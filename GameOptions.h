#pragma once


class GameOptions
{
public:
	GameOptions();
	~GameOptions();
	
	enum Action {
		Nothing,
		Play,
		Options,
		Exit
	};
	struct MenuButton {
	public:
		sf::Text text;
		Action ac;
	};

	Action Show(sf::RenderWindow& window);

private:
	std::list<MenuButton> _buttons;
	Action HandleEvents(sf::RenderWindow& window);
	Action HandleClicks(int x, int y);
};
