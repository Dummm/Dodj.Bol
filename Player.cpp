#include "stdafx.h"
#include "Player.h"


#pragma region  Reflector

Reflector::Reflector() :
	_reflectorBumper(0),
	_reflectorAngle(45),
	_reflectorLength(30.0f),
	_reflectorPointerLength(30.0f),
	_reflectorWidth(90),
	_reflectorSpeed(5.25f),
	_reflectorSize(31) // # + 1(origin)
{
	std::cout << "\n_Player: Reflector loaded.";
}
Reflector::~Reflector() {}

#pragma region Main Functions

void Reflector::LoadReflector(Player* p) {
	_p = p;
	_reflector.setPrimitiveType(sf::TrianglesFan);
	_reflectorPointer.setPrimitiveType(sf::TrianglesFan);
}

void Reflector::UpdateReflector() {
	if (_showReflector)
	{
		ShowReflectorPart(_reflector, _reflectorLength, _reflectorWidth, ReflectorActiveColor);
		_reflectorPointer.resize(0);
	}
	else
	{
		ShowReflectorPart(_reflectorPointer, _reflectorPointerLength, _reflectorWidth, ReflectorInctiveColor);
		_reflector.resize(0);
	}
}

void Reflector::UpdateReflectorColor() {
	ShowReflectorPart(_reflector, _reflectorLength, _reflectorWidth, ReflectorActiveColor);
	_reflectorPointer.resize(0);
}

void Reflector::DrawReflector(sf::RenderWindow& window) {
	window.draw(_reflectorPointer);
	window.draw(_reflector);
}

#pragma endregion Main Functions

#pragma region Gets

sf::VertexArray& Reflector::GetReflector() {
	return _reflector;
}

float Reflector::GetReflectorAngle() {
	return _reflectorAngle;
}

float Reflector::GetReflectorSize() {
	return _reflectorSize;
}

float Reflector::GetReflectorWidth() {
	return _reflectorWidth;
}

#pragma endregion Gets

#pragma region Reflector Control

void Reflector::ShowReflector(bool val) {
	_showReflector = val;
}

void Reflector::MoveReflector(int dir) {
	_reflectorAngle += dir * _reflectorSpeed;
}

void Reflector::ShowReflectorPart(
	sf::VertexArray& part,
	float partLength,
	float partWidth,
	sf::Color color) {
	part.resize(_reflectorSize);
	int segm = part.getVertexCount() - 1;
	sf::Vector2f center = _p->objSprite().getPosition();
	float r = _p->objSprite().getGlobalBounds().width / 2;
	part[0].position = _p->objSprite().getPosition();
	part[0].color = TransparentColor;
	for (int i = _reflectorBumper + 1; i <= segm - _reflectorBumper; i++)
	{
		part[i].position = sf::Vector2f(
			center.x + (r + partLength) * cos((_reflectorAngle + partWidth / (segm - 1) * (i - 1)) * PI / 180),
			center.y + (r + partLength) * sin((_reflectorAngle + partWidth / (segm - 1) * (i - 1)) * PI / -180)
		);
		part[i].color = color;
	}

	// Smooth reflector corners
	for (int i = 1; i <= _reflectorBumper; i++)
	{
		part[i].position = sf::Vector2f(
			center.x +
			(r + partLength / 10 * (7 + 3.0f / _reflectorBumper * i)) *
			cos((_reflectorAngle + partWidth / (segm - 1) * (i - 1)) * PI / 180),
			center.y +
			(r + partLength / 10 * (7 + 3.0f / _reflectorBumper * i)) *
			sin((_reflectorAngle + partWidth / (segm - 1) * (i - 1)) * PI / -180)
		);
		part[segm - i + 1].position = sf::Vector2f(
			center.x +
			(r + partLength / 10 * (7 + 3.0f / _reflectorBumper * i)) *
			cos((_reflectorAngle + partWidth / (segm - 1) * (segm - i + 1 - 1)) * PI / 180),
			center.y +
			(r + partLength / 10 * (7 + 3.0f / _reflectorBumper * i)) *
			sin((_reflectorAngle + partWidth / (segm - 1) * (segm - i + 1 - 1)) * PI / -180)
		);
		part[i].color = part[segm - i + 1].color = color;
	}
	/* // Trying to add solid edges
	part[1].position = sf::Vector2f(
	center.x + (r + partLength / 2) * cos(_reflectorAngle * PI / 180),
	center.y + (r + partLength / 2) * sin(_reflectorAngle * PI / -180)
	);
	part[segm].position = sf::Vector2f(
	center.x + (r + partLength / 2) * cos((_reflectorAngle + partWidth) * PI / 180),
	center.y + (r + partLength / 2) * sin((_reflectorAngle + partWidth) * PI / -180)
	);*/

	//part[1].position = part[segm].position = GetSprite().getPosition();
	//part[1].color = part[segm].color = sf::Color(color.r, color.g, color.b, 0);
	//part[2].color = part[segm - 1].color = sf::Color(color.r, color.g, color.b, 61);
}

#pragma endregion Reflector Control

#pragma endregion Reflector


#pragma region Player

// Default Values (No V-Sync): 0, 0, 0, 50, 300, 0.99f, 270, 40, 40, 0.75f ,10
Player::Player() :
	_score(0) {
	_velX = 0;
	_velY = 0;
	_accel = 50;
	_maxVelocity = 300;
	_friction = 0.9f;
	SetControls(sf::Keyboard::Key::Up,
		sf::Keyboard::Key::Down,
		sf::Keyboard::Key::Left,
		sf::Keyboard::Key::Right,
		sf::Keyboard::Key::Comma,
		sf::Keyboard::Key::Period,
		sf::Keyboard::Key::Slash);
	std::cout << "\n_Player: Player loaded.";
}
Player::~Player() {}

#pragma region Main Functions

bool Player::LoadSecondary(std::vector<Ball*> _ballList) {
	_balls = _ballList;
	LoadReflector(this);
	return true;
}

void Player::SetControls(
	sf::Keyboard::Key up,
	sf::Keyboard::Key down,
	sf::Keyboard::Key left,
	sf::Keyboard::Key right,
	sf::Keyboard::Key refLeft,
	sf::Keyboard::Key refRight,
	sf::Keyboard::Key action) {
	if (!_controls.empty()) _controls.clear();
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Up", up));
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Down", down));
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Left", left));
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Right", right));
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Reflector Left", refLeft));
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Reflector Right", refRight));
	_controls.insert(std::pair<std::string, sf::Keyboard::Key>("Action", action));
}

void Player::SetControlsFull(std::map<std::string, sf::Keyboard::Key> _ctrls) {
	_controls = _ctrls;
}

void Player::Update(float timeDelta) {

	if (sf::Keyboard::isKeyPressed(GetKey("Up")))			   _velY -= _accel;
	if (sf::Keyboard::isKeyPressed(GetKey("Down")))			   _velY += _accel;
	if (sf::Keyboard::isKeyPressed(GetKey("Left")))			   _velX -= _accel;
	if (sf::Keyboard::isKeyPressed(GetKey("Right")))		   _velX += _accel;
	if (sf::Keyboard::isKeyPressed(GetKey("Reflector Left")))  MoveReflector(1);
	if (sf::Keyboard::isKeyPressed(GetKey("Reflector Right"))) MoveReflector(-1);
	if (sf::Keyboard::isKeyPressed(GetKey("Action")))  		   ShowReflector(true);
	else											   		  ShowReflector(false);

	// Friction v1 = Decrease velocity when no key is pressed
	/*if (!sf::Keyboard::isKeyPressed(GetKey("Up")) &&
	!sf::Keyboard::isKeyPressed(GetKey("Down")))
	_velY += ((_velY > 0) - (_velY < 0)) * -_accel;
	if (!sf::Keyboard::isKeyPressed(GetKey("Left")) &&
	!sf::Keyboard::isKeyPressed(GetKey("Right")))
	_velX += ((_velX > 0) - (_velX < 0)) * -_accel;*/

	// Limit player movement to screen edges
	float w = objSprite().getGlobalBounds().width;
	float h = objSprite().getGlobalBounds().height;
	if (objSprite().getPosition().x + w / 2 > _gameArea.x)
		objSprite().setPosition(_gameArea.x - w / 2, objSprite().getPosition().y);
	if (objSprite().getPosition().x - w / 2 < 0)
		objSprite().setPosition(0 + w / 2, objSprite().getPosition().y);
	if (objSprite().getPosition().y + h / 2 > _gameArea.y)
		objSprite().setPosition(objSprite().getPosition().x, _gameArea.y - h / 2);
	if (objSprite().getPosition().y - h / 2 < 0)
		objSprite().setPosition(objSprite().getPosition().x, 0 + h / 2);

	// Cap velocity
	if (_velX > _maxVelocity || _velX < -_maxVelocity)
		_velX = ((_velX > 0) - (_velX < 0)) * _maxVelocity;
	if (_velY > _maxVelocity || _velY < -_maxVelocity)
		_velY = ((_velY > 0) - (_velY < 0)) * _maxVelocity;
	// Stop when velocity is too low
	if (_velX < _accel && _velX > -_accel) _velX = 0;
	if (_velY < _accel && _velY > -_accel) _velY = 0;

	// Friction v2 = Decrease velocity constantly
	_velX *= _friction;
	_velY *= _friction;

	// Move player
	objSprite().move(_velX * timeDelta, _velY * timeDelta);
	UpdateReflector();
}

void Player::DrawSecondary(sf::RenderWindow& window) {
	DrawReflector(window);
}

#pragma endregion Main Functions

#pragma region Score Control

void Player::AddPoint() {
	_score++;
}

void Player::ResetScore() {
	_score = 0;
}

#pragma endregion Score Control

#pragma region Gets

int Player::GetScore() {
	return _score;
}

float Player::GetScale() {
	return _objectScale;
}

sf::Keyboard::Key Player::GetKey(std::string name) {
	std::map<std::string, sf::Keyboard::Key>::const_iterator result = _controls.find(name);
	if (result == _controls.end())
		return sf::Keyboard::Key::Unknown;
	return result->second;
}

#pragma endregion Gets

#pragma endregion Player
