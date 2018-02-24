#include "stdafx.h"
#include "Tiles.h"


Tiles::Tiles() {}
Tiles::~Tiles() {}


void Tiles::Load(std::string location) {
	_file.open(location);
	if (_file.is_open())
		std::cout << "\n_Tiles: File loaded. (" << location << ")";
	else return;
	std::string str, x, y;
	_file >> str;
	if (_texture.loadFromFile(str)) std::cout << "\n_Tiles: Texture loaded.";
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
	_file >> _tileNumber.x >> _tileNumber.y >> _tileSize >> _tileScale >> _mapType;
	if (_mapType == 0) {
		for (int i = 0; i < _tileNumber.y; i++) aux.push_back(sf::Vector2i(0, 0));
		for (int i = 0; i < _tileNumber.x; i++)_map.push_back(aux);
	}
	else if (_mapType == 1) {
		while (!_file.eof()) {
			_file >> str;
			x = str.substr(0, str.find(','));
			y = str.substr(str.find(',') + 1);
			try { aux.push_back(sf::Vector2i(stoi(x), stoi(y))); }
			catch (std::exception& e) { return; }
			if (_file.peek() == '\n') {
				_map.push_back(aux);
				aux.clear();
			}
		}
		_map.push_back(aux);
	}
	std::cout << "\n_Tiles: Tiles loaded.";
}


void Tiles::Draw(sf::RenderWindow& window) {
	for (int i = 0; i < _tileNumber.x; i++) {
		for (int j = 0; j < _tileNumber.y; j++) {
			if (_map[i][j].x == -1) continue;
			_sprite.setPosition(
				i * _sprite.getGlobalBounds().width	 * _tileScale,
				j * _sprite.getGlobalBounds().height * _tileScale
			);
			_sprite.setTextureRect(sf::IntRect(
				_map[i][j].x * _sprite.getGlobalBounds().width,
				_map[i][j].y * _sprite.getGlobalBounds().height,
				_tileSize,
				_tileSize
			));
			window.draw(_sprite);
		}
	}
}

std::vector<std::vector<sf::Vector2i>> Tiles::gMap() {
	return _map;
}

sf::Sprite& Tiles::gSprite() {
	return _sprite;
}


sf::Vector2i Tiles::gTileNumber() {
	return _tileNumber;
}

sf::Vector2f Tiles::gTileArea() {
	return sf::Vector2f(
		_tileNumber.x * _tileSize * _tileScale,
		_tileNumber.y * _tileSize * _tileScale
	);
}