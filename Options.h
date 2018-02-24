#pragma once
#include "GameState.h"
#include "Game.h"

class Game;
class GameSettings;

class Options : public GameState {
public:
	Options(Game* g);
	~Options();
	
	void Show();

private:
	enum Action {
		Nothing,
		Fullscreen,
		Resolution,
		Antialiasing,
		VSync,
		Apply,
		Back
	};
	struct MenuButton {
	public:
		sf::Text text;
		Action ac;
	};
	std::vector<MenuButton*> _buttons;
	Game* _game;
	GameSettings* _settings;

	sf::SoundBuffer _clickBuffer;
	sf::Sound _clickSound;

	void LoadAudio();
	void CreateButtons();
	void LoadStrings();
	void DrawButtons(sf::RenderWindow& window);
	void HandleEvents(sf::RenderWindow& window);
	void HandleClicks(int x, int y);

	void ToggleFullscreen();
	void ChangeResolution();
	void ChangeAntialiasing();
	void ToggleVSync();
	void SaveSettings();
};
