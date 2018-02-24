#pragma once
#include "MainMenu.h"
#include "Options.h"
#include "GamePlay.h"
#include "GameSettings.h"
#include "GameplaySettings.h"
#include "GameState.h"


class Game {
public:
	Game();
	~Game();

	GameSettings _settings;
	GameplaySettings _settingsGameplay;
	
	sf::Texture ballTexture;
	sf::Texture playerTexture;

	sf::Font _font;
	sf::Font _fontBold;
	sf::Font _fontScore;
	
	// Main Functions
	void StartGame();
	void LoadGame();
	void LoadWindow();
	void GameLoop();
	void Quit();

	void PushState(GameState* gs);
	void PopState();
	void ShowState();

	// Gets
	sf::RenderWindow& GetWindow();

	sf::Clock internalClock;

private:
	sf::RenderWindow _window;
	sf::ContextSettings _windowSettings;
	std::stack<GameState*> _gameStates;
};

