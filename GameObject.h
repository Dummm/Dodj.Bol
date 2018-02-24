#pragma once
#include "GameSettings.h"


class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	// Main Functions
	virtual bool Load(
		sf::Vector2f area,
		//std::string location,
		sf::Texture* _t,
		int nr,
		float size,
		float scale,
		sf::Vector2f pos);
	virtual bool LoadSecondary();
	virtual	void Update(float timeDelta);
	virtual void Draw(sf::RenderWindow& window);
	virtual void DrawSecondary(sf::RenderWindow& window);
	virtual	void ResetPosition();
	virtual void SetPosition(sf::Vector2f pos);
	virtual void Delete();

	// Gets
	virtual	sf::Sprite& objSprite();
	virtual sf::Vector2f& objOriginalPosition();
	virtual sf::Vector2f& objVelocity();

protected:
	sf::Vector2f _gameArea;
	float _objectScale; // At load
	float _velX, _velY;
	float _maxVelocity;
	float _accel;
	float _friction;
	float _angle;

private:
	sf::Sprite _sprite;
	sf::Texture* _texture;
	int _spriteNr;
	float _spriteSize;
	sf::Vector2f _originalPosition;
	float _originalAccel;
};
