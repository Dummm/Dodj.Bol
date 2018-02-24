#pragma once
#include "GameState.h"
#include "Game.h"

class Game;

class MainMenu : public GameState {
public:
	MainMenu(Game* s);
	~MainMenu();

	void Show();

private:
	enum Action {
		Nothing,
		CGame,
		JGame, 
		Play,
		Option,
		Exit
	};
	struct MenuButton {
	public:
		sf::Text text;
		Action ac;
	};
	std::vector<MenuButton*> _buttons;
	Game* _game;

	sf::SoundBuffer _clickBuffer;
	sf::Sound _clickSound;

	void LoadAudio();
	void CreateButtons();
	void LoadStrings();
	void DrawButtons(sf::RenderWindow& window);
	void HandleEvents(sf::RenderWindow& window);
	void HandleClicks(int x, int y);
};

