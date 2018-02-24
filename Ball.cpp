#include "stdafx.h"
#include "Ball.h"

#pragma region Pointer

Pointer::Pointer() {}
Pointer::~Pointer() {}

void Pointer::LoadPointer(Ball* b, sf::View* camera, std::string location) {
	if (_texture.loadFromFile(location))
		std::cout << "\n_Ball: Pointer loaded.";
	else return;
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
	_sprite.setOrigin(
		_sprite.getGlobalBounds().width / 2,
		_sprite.getGlobalBounds().height * 3 / 2
	);
	_sprite.setScale(0.6f, 0.6f);

	_ball = b;
	_camera = camera;
}

void Pointer::UpdatePointer() {
	sf::FloatRect rect = sf::FloatRect(
		sf::Vector2f(
			_camera->getCenter().x - _camera->getSize().x / 2,
			_camera->getCenter().y - _camera->getSize().y / 2),
		_camera->getSize());
	if (rect.intersects(_ball->objSprite().getGlobalBounds())) {
		_sprite.setScale(0, 0);
		return;
	}
	_sprite.setScale(0.6f, 0.6f);
	sf::Vector2f pos = 
		_ball->objSprite().getPosition() +
		_ball->gTarget()->objSprite().getPosition();
	pos.x /= 2; pos.y /= 2;

	sf::Vector2f bPos = _ball->objSprite().getPosition();
	float angle = _ball->GetAngle();

	/*if (bPos.x > rect.left + rect.width)
		 pos.x = rect.width;
	if (bPos.x < rect.left)
		 pos.x = 0;

	if (bPos.y > rect.top + rect.height)
		 pos.y = rect.height;
	if (bPos.y < rect.top)
		 pos.y = 0;*/
	
	if (bPos.x >= rect.left + rect.width)
		pos = sf::Vector2f( 
			rect.left + rect.width,
			bPos.y + tan(angle * PI / 180) * (bPos.x - (rect.left + rect.width))
			);

	else if (bPos.x < rect.left)
		pos = sf::Vector2f(
			rect.left,
			bPos.y + tan(angle * PI / 180) * (bPos.x - rect.left)
			//bPos.y + tan(angle * PI / -180) * (rect.left - bPos.x)
		);

	if (bPos.y >= rect.top + rect.height)
		pos = sf::Vector2f(
			bPos.x + tan((-angle + 90) * PI / 180) * (bPos.y - (rect.top + rect.height)),
			rect.top + rect.height
		);

	else if (bPos.y < rect.top)
		pos = sf::Vector2f(
			bPos.x + tan((-angle + 90) * PI / 180) * (bPos.y - rect.top),
			//bPos.x + tan((-angle + 90) * PI / -180) * (rect.top - bPos.y),
			rect.top
		);
		
	_sprite.setPosition(pos);
	_sprite.setRotation(-angle+90);
}

void Pointer::DrawPointer(sf::RenderWindow& window) {
	//window.setView(window.getDefaultView());
	window.draw(_sprite);
	//window.setView(*_camera);
}

#pragma endregion Pointer


#pragma region Trail

Trail::Trail() :
	_colAmount(5),
	_colMax(255),
	_colMin(150) {}
Trail::~Trail() {}

#pragma region Main Functions

void Trail::LoadTrail(Ball* b) {
	_b = b;
	_b->objSprite().setScale(_b->GetScale(), _b->GetScale());
	_trail.setPrimitiveType(sf::TrianglesStrip);
	_trail.resize(26);
	_trailWidth = _b->objSprite().getGlobalBounds().width;
	_trailColor = sf::Color(_colMax, _colMin, _colMin);
	std::cout << "\n_Ball: Trail loaded.";
}

void Trail::UpdateTrailColor() {
	// == -> >=
	// != -> <=

	if (_trailColor.r == _colMax && _trailColor.g != _colMax) {
		if (_trailColor.b == _colMin) _trailColor.g += _colAmount;
		else						  _trailColor.b -= _colAmount;
	}
	if (_trailColor.g == _colMax && _trailColor.b != _colMax) {
		if (_trailColor.r == _colMin) _trailColor.b += _colAmount;
		else  						  _trailColor.r -= _colAmount;
	}
	if (_trailColor.b == _colMax && _trailColor.r != _colMax) {
		if (_trailColor.g == _colMin) _trailColor.r += _colAmount;
		else						  _trailColor.g -= _colAmount;
	}
	_trail[1].color = _trail[0].color = _trailColor;
}

void Trail::UpdateTrail() {
	sf::Vector2f center = _b->objSprite().getPosition();
	_trail[0] = sf::Vector2f(
		center.x + _trailWidth / 2 * cos((_b->GetAngle() + 90) * PI / 180),
		center.y + _trailWidth / 2 * sin((_b->GetAngle() + 90) * PI / -180)
	);
	_trail[1] = sf::Vector2f(
		center.x + _trailWidth / 2 * cos((_b->GetAngle() - 90) * PI / 180),
		center.y + _trailWidth / 2 * sin((_b->GetAngle() - 90) * PI / -180)
	);
	_trail[1].color = _trail[0].color = _trailColor;

	for (int i = _trail.getVertexCount() - 2; i >= 2; i -= 2) {
		// DOAMNEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		sf::Vector2f mij = sf::Vector2f(
			(_trail[i - 2].position.x + _trail[i - 1].position.x) / 2,
			(_trail[i - 2].position.y + _trail[i - 1].position.y) / 2);
		sf::Vector2f aux = sf::Vector2f(
			(_trail[i - 2].position.x - mij.x) * 0.89,
			(_trail[i - 2].position.y - mij.y) * 0.89);

		_trail[i].position = mij + aux;
		_trail[i + 1].position = mij - aux;
		_trail[i].color = _trail[i - 2].color;
		_trail[i + 1].color = _trail[i - 1].color;
	}

	for (
		int i = _trail.getVertexCount() - 1;
		i >= _trail.getVertexCount() / 3 * 2;
		i--) {
		_trail[i].color = sf::Color(
			_trail[i].color.r,
			_trail[i].color.g,
			_trail[i].color.b,
			0 + (255 / _trail.getVertexCount() * 3) *
			(_trail.getVertexCount() - 1 - i)
		);
	}
	UpdateTrailColor();
}

void Trail::DrawTrail(sf::RenderWindow& window) {
	window.draw(_trail);
}

#pragma endregion Main Functions

#pragma endregion Trail


#pragma region Ball

// Default Parameters (No V-Sync): 0, 0, 7.0f, 1000, 270
Ball::Ball() : 
	_reflectionPower(35.0f) {
	_velX = 0;
	_velY = 0;
	_accel = 70.0f; // 25.0f
	_angle = 270;
	_friction = 0.93;
	_maxVelocity = 1000.0f; // 2000
	slowMode = false;
	std::cout << "\n_Ball: Ball loaded.";
}
Ball::~Ball() {
	_reflectSound.resetBuffer();
}

#pragma region Main Functions

void Ball::LoadAudio() {
	if (_reflectBuffer.loadFromFile("Audio\\reflect.wav"))
		std::cout << "\n_Ball: Audio loaded.";
	else return;
	_reflectSound.setBuffer(_reflectBuffer);
	_reflectSound.setVolume(50);
}

bool Ball::LoadSecondary(std::map<std::string, Player*> _playerList, sf::View* camera) {
	_players = _playerList;
	_sender = _players.begin()->second;
	SearchPlayer(_sender);
	objSprite().setScale(_objectScale, _objectScale);

	LoadTrail(this);
	LoadPointer(this, camera, "Images\\BallPointer.png");
	LoadAudio();

	return true;
}

void Ball::Update(float timeDelta) {
	ReflectionCheck();

	_accel = (slowMode) ? 25.f : 70.f;

	_currentPos = objSprite().getPosition();
	_futurePos = _currentTarget->objSprite().getPosition();

	_angle = atan(
		abs(_currentPos.y - _futurePos.y) /
		abs(_currentPos.x - _futurePos.x)) * 180 / PI;
	switch (GetQuadrant()) {
	case 1:	break;
	case 2:	_angle = 180 - _angle; break;
	case 3:	_angle = 180 + _angle; break;
	case 4:	_angle = 360 - _angle; break;
	}

	_velX += cos(_angle *  PI / 180) * _accel;
	_velY += sin(_angle *  PI / 180) * _accel * -1;

	// Cap velocity
	//if (_velX > _maxVelocity || _velX < -_maxVelocity)
	//	_velX = ((_velX > 0) - (_velX < 0)) * _maxVelocity;
	//if (_velY > _maxVelocity || _velY < -_maxVelocity)
	//	_velY = ((_velY > 0) - (_velY < 0)) * _maxVelocity;

	_velX *= _friction;
	_velY *= _friction;

	// Avoid reaching velocity 0 (If possible)
	if (_velX == 0)
		_velX = 0.001f;
	if (_velY == 0)
		_velY = 0.001f;

	objSprite().setRotation(-_angle + 90);
	objSprite().move(_velX * timeDelta, _velY * timeDelta);
	UpdateTrail();
	UpdatePointer();
}

void Ball::DrawSecondary(sf::RenderWindow& window) {
	DrawTrail(window);
	DrawPointer(window);
}

#pragma endregion Main Functions

#pragma region Ball Control

void Ball::SearchPlayer(Player* sender) {
	std::map<std::string, Player*>::iterator player, i;
	player = i = _players.begin();
	while (player != _players.end())  {
		if (player->second != sender) break;
		player++;
	}
	while (i != _players.end())	{
		// Compare distances (Broken)
		if ((/*
			 GetDistance(_currentPos, player->second->GetSprite().getPosition()) >=
			 GetDistance(_currentPos, i->second->GetSprite().getPosition())) &&*/
			i->second != sender))
			player = i;
		i++;
	}
	_sender = sender;
	_currentTarget = player->second;
}

void Ball::ReflectionCheck() {
	sf::VertexArray refl;
	sf::Vector2f center;
	float angle;
	std::map<std::string, Player*>::iterator i = _players.begin();
	while (i != _players.end())	{
		if (i->second == _sender) {
			if (i != _players.end())
				i++;
			continue;
		}
		refl = i->second->GetReflector();
		center = i->second->objSprite().getPosition();
		for (
			int j = 1;
			j < refl.getVertexCount();
			j++) {
			if (GetDistance(objSprite().getPosition(), refl[j].position) <=
				objSprite().getGlobalBounds().width * GetScale() / 2) {
				SearchPlayer(i->second);
				Reflect(
					i->second->GetReflectorAngle() + ((j - 1) * i->second->GetReflectorWidth() / i->second->GetReflectorSize()),
					i->second);
				_reflectSound.play();
				break;
			}
		}
		i++;
	}
}

void Ball::Reflect(float _a, Player* p) {
	_accel += 2.0f;
	float angle = _a;
	_velX = cos(angle *  PI / 180) * _accel *  _reflectionPower;// *-(p->GetVelocity().x / 100 + 1);
	_velY = sin(angle *  PI / 180) * _accel * -_reflectionPower;// * (p->GetVelocity().y / 100 + 1);
}

#pragma endregion Ball Control

#pragma region Gets

float Ball::GetDistance(sf::Vector2f a, sf::Vector2f b) {
	return sqrt(abs(a.y - b.y) * abs(a.y - b.y) +
		abs(a.x - b.x) * abs(a.x - b.x));
}

float Ball::GetScale() {
	return _objectScale;
}

float Ball::GetAngle() {
	return _angle;
}

int Ball::GetQuadrant() {
	if (_currentPos.x <= _futurePos.x)
		if (_currentPos.y >= _futurePos.y)
			return 1;
		else return 4;
	else
		if (_currentPos.y >= _futurePos.y)
			return 2;
		else return 3;
}

Player* Ball::gTarget() {
	return _currentTarget;
}

#pragma endregion Gets

#pragma endregion Ball
