#pragma once
#include "Ball.h"
//#include "Player.h"
//#include "GameObject.h"

class Ball;

class Trail
{
public:
	Trail();
	~Trail();

	virtual void LoadTrail(Ball* b);
	virtual void UpdateTrail();
	virtual void UpdateTrailColor();
	virtual void DrawTrail(sf::RenderWindow& window);

private:
	sf::VertexArray _trail;
	sf::Color _trailColor;
	Ball* _b;
	float _trailWidth;
};
