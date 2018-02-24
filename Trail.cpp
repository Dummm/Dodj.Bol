#include "stdafx.h"
#include "Trail.h"

#define PI 3.14159265

Trail::Trail() {}
Trail::~Trail() {}

void Trail::LoadTrail(Ball* b) {
	_b = b;

	_b->GetSprite().setScale(_b->GetScale(), _b->GetScale());
	_trail.setPrimitiveType(sf::TrianglesStrip);
	_trail.resize(26);
	_trailWidth = _b->GetSprite().getGlobalBounds().width;
	_trailColor = sf::Color::Red;
}

void Trail::UpdateTrailColor() {
	if (_trailColor.r == 255 && _trailColor.g != 255) {
		if (_trailColor.b == 0)
			_trailColor.g += 15;
		else
			_trailColor.b -= 15;
	}
	if (_trailColor.g == 255 && _trailColor.b != 255) {
		if (_trailColor.r == 0)
			_trailColor.b += 15;
		else
			_trailColor.r -= 15;
	}
	if (_trailColor.b == 255 && _trailColor.r != 255) {
		if (_trailColor.g == 0)
			_trailColor.r += 15;
		else
			_trailColor.g -= 15;
	}
	_trail[1].color = _trail[0].color = _trailColor;
}

void Trail::UpdateTrail() {
	//float _angle = 180;
	sf::Vector2f center = _b->GetSprite().getPosition();
	_trail[0] = sf::Vector2f(
		center.x + _trailWidth / 2 * cos((_b->GetAngle() + 90) * PI / 180),
		center.y + _trailWidth / 2 * sin((_b->GetAngle() + 90) * PI / -180)
	);

	_trail[1] = sf::Vector2f(
		center.x + _trailWidth / 2 * cos((_b->GetAngle() - 90) * PI / 180),
		center.y + _trailWidth / 2 * sin((_b->GetAngle() - 90) * PI / -180)
	);

	_trail[1].color = _trail[0].color = _trailColor;
	//_trailVertex += 2;
	//if (_trailVertex >= _trail.getVertexCount())
	//	_trailVertex = _trail.getVertexCount()-1;
	for (int i = _trail.getVertexCount() - 2; i >= 2; i -= 2)
	{
		_trail[i].position = _trail[i - 2].position;
		_trail[i].color = _trail[i - 2].color;
		_trail[i + 1].position = _trail[i - 1].position;
		_trail[i + 1].color = _trail[i - 1].color;
		//if (_trail[i + 2].position == sf::Vector2f(0, 0))
		//continue;
	}
	for (
		int i = _trail.getVertexCount() - 1;
		i >= _trail.getVertexCount() / 3 * 2;
		i--)
	{
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