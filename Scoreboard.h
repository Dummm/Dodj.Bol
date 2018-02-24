#pragma once
#include "Player.h"


class Scoreboard {
public:
	Scoreboard();
	~Scoreboard();

	// Main Functions
	void LoadAudio();
	void Load(sf::Vector2f res, sf::Clock* internalClock);
	void Update(std::map<std::string, Player*> _playerList);
	void UpdateShadows();
	void UpdatePosition();
	void Draw(sf::RenderWindow& window);

	// Timer Control
	void Start();
	void Pause();
	void Stop();
	void Countdown();

	// Gets
	bool Started();
	bool Paused();
	bool Counted();
	int Time();
	void CheckScores();

private:
	sf::Vector2f _screenRes;
	std::map<std::string, Player*> _players;

	int aux;
	int prevNumber;
	sf::SoundBuffer _countdownBuffer;
	sf::Sound _countdownSound;

	sf::Font _font;
	sf::Text _timer;
	sf::Text _timerSh;
	sf::Text _score1;
	sf::Text _score1Sh;
	sf::Text _score2;
	sf::Text _score2Sh;
	sf::Text _countdown;
	sf::Text _countdownSh;
	int _scoreSize;
	int _timerSize;
	int _countdownSize;

	sf::Clock* _internalClock;
	sf::Time _time;
	sf::Time _startTime;
	sf::Time _pausedTime;
	sf::Time _countStart;
	bool _started;
	bool _paused;
	bool _startedCount;
	bool _counted;
	float _count;
};
