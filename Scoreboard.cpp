#include "stdafx.h"
#include "Scoreboard.h"


#pragma region Scoreboard

Scoreboard::Scoreboard() :
	_startTime(sf::Time::Zero),
	_pausedTime(sf::Time::Zero),
	_started(false),
	_paused(false),
	_counted(true),
	_startedCount(false),
	_count(3),
	_scoreSize(35),
	_timerSize(50),
	prevNumber(0) {}
Scoreboard::~Scoreboard() {
	_countdownSound.resetBuffer();
	_countdownBuffer.~SoundBuffer();
	std::cout << "\n_Scoreboard: Scoreboard loaded.";
}

#pragma region Main Functions

void Scoreboard::LoadAudio() {
	if (_countdownBuffer.loadFromFile("Audio\\click.wav"))
		std::cout << "\n_MainMenu: Audio loaded";
	else return;
	_countdownSound.setBuffer(_countdownBuffer);
	_countdownSound.setVolume(50);
}

void Scoreboard::Load(sf::Vector2f res, sf::Clock* internalClock) {
	_screenRes = res;
	_internalClock = internalClock;

	//if (!_font.loadFromFile("Fonts\\DaysOne-Regular.ttf"))
	//if (!_font.loadFromFile("Fonts\\Bungee-Regular.ttf"))
	if (!_font.loadFromFile("Fonts\\Oswald-Regular.ttf"))
		return;

	_timer.setFont    (_font);
	_score1.setFont   (_font);
	_score2.setFont	  (_font);
	_countdown.setFont(_font);

	_timer.setCharacterSize    (_screenRes.y / 15);
	_score1.setCharacterSize   (_screenRes.y / 22);
	_score2.setCharacterSize   (_screenRes.y / 22);
	_countdown.setCharacterSize(_screenRes.y / 7.5f);

	_timer.setFillColor    (GameFGColor);
	_score1.setFillColor   (GameFGColor);
	_score2.setFillColor   (GameFGColor);
	_countdown.setFillColor(GameFGColor);

	UpdatePosition();
	UpdateShadows();

	LoadAudio();
	Start();
}

void Scoreboard::Update(std::map<std::string, Player*> _playerList) {
	if (_started) {
		if (_paused) _time = _pausedTime;
		else		 _time = _internalClock->getElapsedTime() - _startTime;	}
	else			 _time = sf::Time::Zero;
	_players = _playerList;
	_timer.setString(std::to_string((int)_time.asSeconds()));
	CheckScores();
	Countdown();
	UpdatePosition();
	UpdateShadows();
}

void Scoreboard::UpdateShadows() {
	_timerSh = _timer;
	_score1Sh = _score1;
	_score2Sh = _score2;
	_countdownSh = _countdown;

	_timerSh.setFillColor		(GameSHColor);
	_score1Sh.setFillColor		(GameSHColor);
	_score2Sh.setFillColor		(GameSHColor);
	_countdownSh.setFillColor	(GameSHColor);

	_timerSh.setPosition(_timerSh.getPosition() + sf::Vector2f(4.25f, 4.25f));
	_score1Sh.setPosition(_score1Sh.getPosition() + sf::Vector2f(1.5f, 1.5f));
	_score2Sh.setPosition(_score2Sh.getPosition() + sf::Vector2f(1.5f, 1.5f));
	_countdownSh.setPosition(_countdownSh.getPosition() + sf::Vector2f(5, 5));
}

void Scoreboard::UpdatePosition() {
	int dist = _screenRes.y / 50;

	_timer.setOrigin(
		_timer.getGlobalBounds().width  / 2,
		_timer.getGlobalBounds().height / 2);
	_score1.setOrigin(
		0,
		_score1.getGlobalBounds().height / 2);
	_score2.setOrigin(
		_score2.getGlobalBounds().width,
		_score2.getGlobalBounds().height / 2);
	_countdown.setOrigin(
		_countdown.getGlobalBounds().width  / 2,
		_countdown.getGlobalBounds().height / 2);

	_timer.setPosition(
		_screenRes.x / 2,
		_timer.getGlobalBounds().height / 2 + dist);
	_score1.setPosition(
		dist,
		_timer.getGlobalBounds().height / 2 + dist);
	_score2.setPosition(
		_screenRes.x - dist,
		_timer.getGlobalBounds().height / 2 + dist);
	_countdown.setPosition(
		_screenRes.x / 2,
		_screenRes.y / 2);
}

void Scoreboard::Draw(sf::RenderWindow& window) {
	window.setView(window.getDefaultView());

	window.draw(_timerSh);	window.draw(_timer);
	window.draw(_score1Sh);	window.draw(_score1);
	window.draw(_score2Sh);	window.draw(_score2);
	
	if (_counted == false && _startedCount == true)	{
		window.draw(_countdownSh); window.draw(_countdown);
		if (_countdown.getString().toAnsiString() != "") 
			aux = std::stoi(_countdown.getString().toAnsiString());
		if (aux != prevNumber) {
			prevNumber = aux;
			_countdownSound.play();
		}
	}
}

#pragma endregion Main Functions

#pragma region Timer Control

void Scoreboard::Start() {
	UpdatePosition();
	_counted = false;
	_countStart = _startTime = _internalClock->getElapsedTime();
	_startedCount = true;

	//_started = true;
	//_paused = false;

	//_startTime = _internalClock->getElapsedTime();
	_pausedTime = sf::Time::Zero;

	_started = true;
	_paused = true;
	_counted = true;
	_startedCount = false;
}

void Scoreboard::Pause() {
	if (_started) {
		if (!_paused) {
			_paused = true;
			_pausedTime = _internalClock->getElapsedTime() - _startTime;
			_startTime = sf::Time::Zero;
		}
		else {
			//_paused = false;
			_counted = false;
			_countStart = _startTime = _internalClock->getElapsedTime();
			_startedCount = true;
			//_startTime = _internalClock->getElapsedTime() - _pausedTime;
			//_pausedTime = sf::Time::Zero;
		}
	}
}

void Scoreboard::Stop() {
	//_started = _paused = false;
	_paused = true;
	_startTime = _pausedTime = sf::Time::Zero;
}

void Scoreboard::Countdown() {
	if (_counted) return;

	if (_internalClock->getElapsedTime() - _countStart > sf::seconds(_count)) {
		//if (_paused)
		//_pausedTime = sf::Time::Zero;

		_startTime = _internalClock->getElapsedTime() - _pausedTime;

		_counted = true;
		_startedCount = false;
		_started = true;
		_paused = false;

	}
	else
		_countdown.setString(std::to_string(
		(int)_count - 
		(int)(_internalClock->getElapsedTime() - _countStart).asSeconds()));
}

#pragma endregion Timer Control

#pragma region Gets

bool Scoreboard::Started() {
	return _started;
}

bool Scoreboard::Paused() {
	return _paused;
}

bool Scoreboard::Counted() {
	return _counted;
}

int Scoreboard::Time() {
	std::string aux = _timer.getString();
	return std::stoi(aux);
}

void Scoreboard::CheckScores() {
	std::map<std::string, Player*>::iterator i;
	i = _players.begin();
	_score2.setString(std::to_string(i->second->GetScore())); i++;
	_score1.setString(std::to_string(i->second->GetScore()));
}

#pragma endregion Gets

#pragma endregion Scoreboard