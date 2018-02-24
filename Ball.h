#pragma once
#include "GameObject.h"
#include "Player.h"
class Player;
class Ball;


class Pointer
{
public:
	Pointer();
	~Pointer();

	virtual void LoadPointer(Ball* b, sf::View* camera, std::string location);
	virtual void UpdatePointer();
	virtual void DrawPointer(sf::RenderWindow& window);

private:
	Ball* _ball;
	sf::View* _camera;
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _scale;
};

class Trail
{
public:
	Trail();
	~Trail();

	// Main Functions
	virtual void LoadTrail(Ball* b);
	virtual void UpdateTrail();
	virtual void UpdateTrailColor();
	virtual void DrawTrail(sf::RenderWindow& window);

private:
	sf::VertexArray _trail;
	sf::Color _trailColor;
	float _trailWidth;
	int _colAmount;
	int _colMin;
	int _colMax;
	Ball* _b;
};


class Ball : public GameObject, public Trail, public Pointer {
public:
	Ball();
	~Ball();

	bool slowMode;
	sf::SoundBuffer _reflectBuffer;
	sf::Sound _reflectSound;

	// Main Functions
	void LoadAudio();
	bool LoadSecondary(std::map<std::string, Player*> _playerList, sf::View* camera);
	void Update(float timeDelta);
	void DrawSecondary(sf::RenderWindow& window);

	// Ball Control
	void SearchPlayer(Player* sender);
	void ReflectionCheck();
	void Reflect(float _a, Player* p);

	// Gets
	float GetDistance(sf::Vector2f a, sf::Vector2f b);
	float GetScale();
	float GetAngle();
	int GetQuadrant();
	Player* gTarget();
	
private:
	std::map<std::string, Player*> _players;
	sf::Vector2f _currentPos;
	sf::Vector2f _futurePos;
	Player* _currentTarget;
	Player* _sender;
	float _reflectionPower;
};
