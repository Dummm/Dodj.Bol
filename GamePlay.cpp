#include "stdafx.h"
#include "GamePlay.h"


#pragma region Game Events

GameEvents::GameEvents() {}
GameEvents::~GameEvents() {}

void GameEvents::Collisions(GamePlay* g) {
	std::map<std::string, Player*> _players = g->_playerList;
	std::vector<Ball*> _balls = g->_ballList;
	std::map<std::string, Player*>::iterator iP;
	std::vector<Ball*>::iterator iB;
	std::vector<sf::RectangleShape*>::iterator i, j;
	Player* player; Ball* ball;

	iP = _players.begin();
	while (iP != _players.end()) {
		iB = _balls.begin();
		while (iB != _balls.end()) {
			player = iP->second; ball = (*iB);
			if (CheckCollision(ball, player)) {
				IncrementScore(_players, player);
				g->ResetPositions(player);
				g->_score.Start();
				g->_score.Pause();
				break;
			}
			iB++;
		}
		iP++;
	}

}

bool GameEvents::CheckCollision(Ball* b, Player* p) {
	sf::Sprite sprA, sprB;
	float scaleA, scaleB;
	sprA = b->objSprite(); scaleA = b->GetScale();
	sprB = p->objSprite(); scaleB = p->GetScale();
	//scaleA = scaleB = 1;

	float A = abs(sprA.getPosition().x - sprB.getPosition().x);
	float B = abs(sprA.getPosition().y - sprB.getPosition().y);
	float dist =
		sprA.getGlobalBounds().width * scaleA / 2.0f +
		sprB.getGlobalBounds().width * scaleB / 2.0f;
	if (A*A + B*B <= dist * dist)
		return true;
	return false;
}

void GameEvents::IncrementScore(
	std::map<std::string, Player*> _players,
	Player* player) {
	std::map<std::string, Player*>::iterator iP = _players.begin();
	while (iP != _players.end()) {
		if (iP->second != player)
			iP->second->AddPoint();
		iP++;
	}
}

#pragma endregion Game Events



GamePlay::GamePlay(Game* g) :
	slowMode(false) {
	_game = g;
	Load();
	_score.Pause();
}
GamePlay::~GamePlay() {}

void GamePlay::Show() {
	Update();
	Draw(_game->GetWindow());
	HandleEvents(_game->GetWindow());
}

void GamePlay::Load() {
	_background.Load("Data\\Tiles.txt");
	_gameArea = _background.gTileArea();

	_playerList.clear();
	_ballList.clear();

	std::string ballLoc = "Images\\Ball.png";
	std::string playerLoc = "Images\\Players.png";
	ballTexture.loadFromFile(ballLoc);
	playerTexture.loadFromFile(playerLoc);

	srand(time(NULL));
	Player* P1 = new Player();
	Player* P2 = new Player();
	//P1->Load(_gameArea, &playerTexture, rand() % 7, 64, 0.75f, sf::Vector2f(1.0f / 5 * 4, 1.0f / 2));
	//P2->Load(_gameArea, &playerTexture, rand() % 7, 64, 0.75f, sf::Vector2f(1.0f / 5 * 1, 1.0f / 2));
	P1->Load(_gameArea, &playerTexture, _game->_settingsGameplay.gTextureP1(), 64, 0.75f, sf::Vector2f(1.0f / 5 * 4, 1.0f / 2));
	P2->Load(_gameArea, &playerTexture, _game->_settingsGameplay.gTextureP2(), 64, 0.75f, sf::Vector2f(1.0f / 5 * 1, 1.0f / 2));
	P1->LoadSecondary(_ballList);
	P2->LoadSecondary(_ballList);
	//P2->SetControls(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Key::Q, sf::Keyboard::Key::E, sf::Keyboard::F);
	P1->SetControlsFull(_game->_settingsGameplay.gControlsP1());
	P2->SetControlsFull(_game->_settingsGameplay.gControlsP2());
	_playerList.insert(std::pair<std::string, Player*>("Player 1", P1));
	_playerList.insert(std::pair<std::string, Player*>("Player 2", P2));

	Ball* Ball1 = new Ball();
	Ball1->Load(_gameArea, &ballTexture, 0, 64, 0.55f, sf::Vector2f(1.0f / 2, 1.0f / 2));
	Ball1->LoadSecondary(_playerList, &_camera);
	_ballList.push_back(Ball1);

	_score.Load(_game->_settings.gResolution(), &(_game->internalClock));
	_score.Update(_playerList);

	_camera.reset(sf::FloatRect(sf::Vector2f(0, 0), _game->_settings.gResolution()));

	_dt = sf::seconds(1.f / 60.f);
	_updateT = sf::Time::Zero;
}

void GamePlay::Draw(sf::RenderWindow& window) {
	window.setView(_camera);
	window.clear(GameBGColor);

	_background.Draw(window);

	std::vector<Ball*>::iterator iB = _ballList.begin();
	while (iB != _ballList.end())
		(*iB++)->Draw(window);
	std::map<std::string, Player*>::iterator iP = _playerList.begin();
	while (iP != _playerList.end())
		iP++->second->Draw(window);
	_score.Draw(window);

	window.display();
	window.setView(window.getDefaultView()); // Test
}

void GamePlay::Update() {
	Collisions(this);


	_updateT += tick.restart();
	while (_updateT > _dt) {
		if (_score.Paused() == true || _score.Started() == false)
			UpdateObjects(0);
		else UpdateObjects((_dt * ((slowMode) ? .5f : 1.f)).asSeconds());
		_updateT -= _dt;
	}

	UpdateCamera();

	BallSpawner(_score.Time());

	_game->GetWindow().setTitle("Dodj.Bol [" +
		std::to_string(1.0f / tick.getElapsedTime().asSeconds()) + "]");
	
}

void GamePlay::UpdateObjects(float timeDelta) {
	std::vector<Ball*>::iterator iB = _ballList.begin();
	while (iB != _ballList.end()) {
		(*iB)->Update(timeDelta);
		(*iB++)->slowMode = slowMode;
	}
	std::map<std::string, Player*>::iterator iP = _playerList.begin();
	while (iP != _playerList.end())
		iP++->second->Update(timeDelta);
	_score.Update(_playerList);
}

void GamePlay::UpdateCamera() {
	sf::Vector2f a, aOr, b, bOr;
	GameSettings* _settings = &(_game->_settings);
	std::map<std::string, Player*>::iterator i = _playerList.begin();
	a = i->second->objSprite().getPosition(); aOr = i++->second->objOriginalPosition();
	b = i->second->objSprite().getPosition(); bOr = i->second->objOriginalPosition();
	float ratio = (float)_settings->gResolution().x / (float)_settings->gResolution().y;
	sf::Vector2f distOr = sf::Vector2f(
		abs(aOr.x - bOr.x) * (float)_gameArea.x,
		abs(aOr.y - bOr.y) * (float)_gameArea.y);
	sf::Vector2f dist = sf::Vector2f(
		abs(a.x - b.x),
		abs(a.y - b.y));

	_camera.setSize(dist);
	if (distOr.x > dist.x) _camera.setSize(distOr.x, _camera.getSize().y);
	if (distOr.y > dist.y) _camera.setSize(_camera.getSize().y, distOr.y);

	if (_camera.getSize().x / _camera.getSize().y < ratio)
		_camera.setSize(_camera.getSize().y * ratio, _camera.getSize().y);
	if (_camera.getSize().y / _camera.getSize().x < 1 / ratio)
		_camera.setSize(_camera.getSize().x, _camera.getSize().x / ratio);

	_camera.setSize(_camera.getSize().x * 1.25f, _camera.getSize().y * 1.25f);

	_camera.setCenter(
		(a.x + b.x) / 2,
		(a.y + b.y) / 2);
}

void GamePlay::BallSpawner(int time) {
	if (time / 10 + 1 == _ballList.size()) return;
	else if ((time / 10 + 1 > _ballList.size())) {
		Ball* b = new Ball();
		b->Load(_gameArea, &ballTexture, 0, 64, 0.55f, sf::Vector2f(1.0f / 2, 1.0f / 2));
		b->LoadSecondary(_playerList, &_camera);
		_ballList.push_back(b);
	}
	else _ballList.erase(--_ballList.end());
}

void GamePlay::HandleEvents(sf::RenderWindow& window) {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window.close();
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
			_game->PopState();
		if ((e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::P) ||
			(e.type == sf::Event::LostFocus  && !_score.Paused()))
			_score.Pause();
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::O)
			Restart();
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::LBracket)
			slowMode = !slowMode;
	}
}

void GamePlay::HandleClicks(int x, int y) {
	;
}

void GamePlay::Restart() {
	ResetScores();
	_score.Start();
	_score.Stop();
	ResetPositions(_playerList.begin()->second);
	UpdateObjects(0);
	Load();
}

void GamePlay::ResetScores() {
	std::map<std::string, Player*>::iterator iP = _playerList.begin();
	while (iP != _playerList.end())
		iP++->second->ResetScore();
}

void GamePlay::ResetPositions(Player* sender) {
	std::map<std::string, Player*>::iterator iP = _playerList.begin();
	while (iP != _playerList.end())
		iP++->second->ResetPosition();

	Ball* b = (*_ballList.begin());
	b->ResetPosition();
	b->objVelocity() = sf::Vector2f(0.0001f, 0.0001f);
	b->SearchPlayer(sender);
}
