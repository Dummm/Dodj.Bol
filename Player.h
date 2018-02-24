#pragma once
#include "GameObject.h"
#include "Ball.h"
class Ball;
class Player;

class Reflector
{
public:
	Reflector();
	~Reflector();
	
	// Main Funtions
	virtual void LoadReflector(Player* p);
	virtual void UpdateReflector();
	virtual void UpdateReflectorColor();
	virtual void DrawReflector(sf::RenderWindow& window);

	// Gets
	virtual sf::VertexArray& GetReflector();
	virtual float GetReflectorAngle();
	virtual float GetReflectorSize();
	virtual float GetReflectorWidth();

protected:
	// Reflector Control
	virtual void ShowReflector(bool val);
	virtual void MoveReflector(int dir);
	void ShowReflectorPart(sf::VertexArray& part, float partLength, float partWidth, sf::Color color);

private:
	Player* _p;
	bool _showReflector;
	sf::VertexArray _reflector;
	sf::VertexArray _reflectorPointer;

	float _reflectorBumper; // Smooth reflector corners 
	float _reflectorAngle;
	float _reflectorLength;
	float _reflectorPointerLength;
	float _reflectorWidth; // Degrees
	float _reflectorSpeed;
	float _reflectorSize; // Vertices
};


class Player : public GameObject, public Reflector {
public:
	Player();
	~Player();

	// Main Functions
	bool LoadSecondary(std::vector<Ball*> _ballList);
	void SetControls(
		sf::Keyboard::Key up,
		sf::Keyboard::Key down, 
		sf::Keyboard::Key left, 
		sf::Keyboard::Key right, 
		sf::Keyboard::Key refLeft, 
		sf::Keyboard::Key refRight, 
		sf::Keyboard::Key action);
	void SetControlsFull(std::map<std::string, sf::Keyboard::Key> _ctrls);
	void Update(float timeDelta);
	void DrawSecondary(sf::RenderWindow& window);

	// Score Control
	void AddPoint();
	void ResetScore();

	// Gets
	sf::Keyboard::Key GetKey(std::string name);
	int GetScore();
	float GetScale();

private:
	std::map<std::string, sf::Keyboard::Key> _controls;
	std::vector<Ball*> _balls;
	int _score;
};
