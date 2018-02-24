#pragma once


class Tiles
{
public:
	Tiles();
	~Tiles();
	
	void Load(std::string location);
	void Draw(sf::RenderWindow& window);


	std::vector<std::vector<sf::Vector2i>> gMap();
	sf::Sprite& gSprite();
	sf::Vector2i gTileNumber();
	sf::Vector2f gTileArea();

private:
	sf::Texture tx;
	sf::Sprite _tileSet;

	std::fstream _file;
	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::Vector2i _tileNumber;
	float _tileSize;
	float _tileScale;
	int _mapType;
	std::vector<std::vector<sf::Vector2i>> _map;
				std::vector<sf::Vector2i> aux;

};
