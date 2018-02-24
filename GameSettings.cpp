#include "stdafx.h"
#include "GameSettings.h"


GameSettings::GameSettings() {}
GameSettings::~GameSettings() {}

void GameSettings::Load(std::string location) {
	_settings.clear();
	_location = location;
	std::string aux;
	_file.open(_location);
	while(std::getline(_file, aux)) 
		_settings.push_back(std::stoi(aux));
	_file.close();
	std::cout << "\n_GameSettings: Settings loaded.";
}

void GameSettings::Save() {
	_file.open(_location);
	for (int i = 0; i < _settings.size(); i++) {
		_file << _settings[i];
		if (i < _settings.size() - 1) _file << "\n";
	}
	_file.close();
	std::cout << "\n_GameSettings: Settings saved.";
}

int  GameSettings::gSettingByIndex(int i) {
	return _settings[i];
}
void GameSettings::sSettingByIndex(int i, int val) {
	_settings[i] = val;
}

int  GameSettings::gFullscreen() {
	return _settings[0];
}
void GameSettings::sFullscreen(int val) {
	_settings[0] = val;
}

sf::Vector2f GameSettings::gResolution() {
	return sf::Vector2f(_settings[1], _settings[2]);
}
void		 GameSettings::sResolution(sf::Vector2f val) {
	_settings[1] = val.x;
	_settings[2] = val.y;
}

int GameSettings::gAntialiasing() {
	return _settings[3];
}
void GameSettings::sAntialiasing(int val) {
	_settings[3] = val;
}

int GameSettings::gVSync() {
	return _settings[4];
}
void GameSettings::sVSync(int val) {
	_settings[4] = val;
}
