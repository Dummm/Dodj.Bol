#pragma once
#include "GameState.h"
#include "Game.h"

#include "Player.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "Tiles.h"

class Game;
class GamePlay;


class GameEvents {
public:
	GameEvents();
	~GameEvents();

	virtual void Collisions(GamePlay* g);
	virtual bool CheckCollision(Ball* b, Player* p);
	virtual void IncrementScore(
		std::map<std::string, Player*> _players,
		Player* player);

private:
};

class GamePlay : public GameState, public GameEvents {
public:
	GamePlay(Game* g);
	~GamePlay();

	std::map<std::string, Player*> _playerList;
	std::vector<Ball*> _ballList;
	Scoreboard _score;
	Tiles _background;
	sf::Vector2f _gameArea;

	sf::Texture ballTexture;
	sf::Texture playerTexture;
	
	sf::View _camera;

	bool slowMode;

	sf::Time _updateT;
	sf::Time _dt;
	sf::Clock tick;

	void Show();

	void Load();
	void Draw(sf::RenderWindow& window);
	void Update();
	void UpdateObjects(float timeDelta);
	void UpdateCamera();
	void BallSpawner(int time);
	void HandleEvents(sf::RenderWindow& window);
	void HandleClicks(int x, int y);

	void Restart();
	void ResetScores();
	void ResetPositions(Player* sender);
	Game* _game;
private:
};
