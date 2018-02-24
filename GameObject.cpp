#include "stdafx.h"
#include "GameObject.h"


#pragma region Game Object

GameObject::GameObject() {}
GameObject::~GameObject() {}

#pragma region Main Functions

bool GameObject::Load(
	sf::Vector2f area,
	//std::string location,
	sf::Texture* _t,
	int nr,
	float size,
	float scale,
	sf::Vector2f pos) {
	/*if (_texture.loadFromFile(location) == false) return false;*/
	_texture = _t;
	_texture->setSmooth(true);
	_sprite.setTexture(*_texture);

	_gameArea = area;
	_spriteNr = nr;
	_spriteSize = size;

	_sprite.setTextureRect(sf::IntRect(
		_spriteNr * _spriteSize, 0,
		_spriteSize, _spriteSize
	));

	_objectScale = scale;
	_sprite.setOrigin(
		_sprite.getGlobalBounds().width / 2 ,
		_sprite.getGlobalBounds().height / 2);
	objSprite().setScale(_objectScale, _objectScale);

	SetPosition(pos);
	_originalAccel = _accel;

	return true;
}

bool GameObject::LoadSecondary() {
	return true;
}

void GameObject::Update(float timeDelta) {}

void GameObject::Draw(sf::RenderWindow& window) {
	DrawSecondary(window);
	window.draw(_sprite);
}

void GameObject::DrawSecondary(sf::RenderWindow& window) {}

void GameObject::ResetPosition() {
	this->SetPosition(_originalPosition);
	_accel = _originalAccel;
}

void GameObject::SetPosition(sf::Vector2f pos) {
	_sprite.setPosition(
		_gameArea.x * pos.x,
		_gameArea.y * pos.y);
	_originalPosition = pos;
}

void GameObject::Delete() {
	delete this;
}

#pragma endregion Main Functions

#pragma region Gets

sf::Sprite& GameObject::objSprite() {
	return _sprite;
}

sf::Vector2f& GameObject::objOriginalPosition() {
	return _originalPosition;
}

sf::Vector2f& GameObject::objVelocity() {
	return sf::Vector2f(_velX, _velY);
}

#pragma endregion Gets

#pragma endregion Game Object
