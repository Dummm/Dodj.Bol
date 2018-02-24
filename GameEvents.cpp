/*8#include "stdafx.h"
#include "GameEvents.h"

GameEvents::GameEvents() {}
GameEvents::~GameEvents() {}

void GameEvents::Collisions(Game* g) {
	std::map<std::string, Player*> _players = g->_playerList;
	std::vector<Ball*> _balls = g->_ballList;
	Player* player; Ball* ball;
	std::map<std::string, Player*>::iterator ip;
	std::vector<Ball*>::iterator ib;
	std::vector<sf::RectangleShape*>::iterator i, j;

	ip = _players.begin();
	while (ip != _players.end())
	{
		ib = _balls.begin();
		while (ib != _balls.end())
		{
			player = ip->second; ball = (*ib);
			if (CheckCollision(ball, player))
			{
				//ball->SearchPlayer(player);
				IncrementScore(_players, player);
				g->ResetPositions(player);
				g->Score.Pause();
				g->Score.Start();
				break;
			}
			ib++;
		}
		ip++;
	}
	
}

bool GameEvents::CheckCollision(Ball* b, Player* p) {
	sf::Sprite sprA, sprB;
	float scaleA, scaleB;
	sprA = b->objSprite(); sprB = p->objSprite();
	scaleA = b->GetScale(); scaleB = p->GetScale();
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
	std::map<std::string, Player*>::iterator iP;
	iP = _players.begin();
	while (iP != _players.end())
	{
		if (iP->second != player)
			iP->second->AddPoint();
		iP++;
	}
}
*/