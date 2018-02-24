#include "stdafx.h"
#include "Game.h"


#pragma region Game

Game::Game() {}
Game::~Game() {}

#pragma region Game Functions

void Game::StartGame() {
	LoadGame();
	GameState* gs = new MainMenu(this);
	PushState(gs);
	GameLoop();
	Quit();
}

void Game::LoadGame() {
	_settings.Load("Data\\Settings.txt");
	if (!_font.loadFromFile("Fonts\\SpaceMono-Regular.ttf")) {
		std::cout << "sp."; Quit(); }
	if (!_fontBold.loadFromFile("Fonts\\SpaceMono-Bold.ttf")) {
		std::cout << "sp."; Quit(); }
	if (!_fontScore.loadFromFile("Fonts\\Oswald-Regular.ttf")) {
		std::cout << "sp."; Quit(); }
	std::cout << "\n_Game: Fonts loaded.";

	_settingsGameplay.Load("Data\\GameplaySettings.txt");

	LoadWindow();
}

void Game::LoadWindow() {
	_windowSettings.antialiasingLevel = _settings.gAntialiasing();
	_window.create(
		sf::VideoMode(_settings.gResolution().x, _settings.gResolution().y),
		"Dodj.Bol",
		_settings.gFullscreen() == 1 ?
			sf::Style::Fullscreen :
			sf::Style::Close | sf::Style::Titlebar,
		_windowSettings);
	if (_settings.gVSync() == 1)
		 _window.setVerticalSyncEnabled(true);
	else _window.setVerticalSyncEnabled(false);
	//_window.setFramerateLimit(60);
	std::cout << "\n_Game: Window loaded.";
}

void Game::GameLoop() {
	while (_window.isOpen()) ShowState();
}

void Game::Quit() {
	_window.close();
}

#pragma endregion Main Functions

#pragma region Game States

void Game::PushState(GameState* gs){
	_gameStates.push(gs);
}

void Game::PopState() {
	delete _gameStates.top();
	_gameStates.pop();
}

void Game::ShowState() {
	if (_gameStates.empty()) return;
	_gameStates.top()->Show();
}

#pragma endregion Game States

#pragma region Gets

sf::RenderWindow& Game::GetWindow() {
	return _window;
}

#pragma endregion Gets

#pragma endregion Game
