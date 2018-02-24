#pragma once
#include "Game.h"
#include "GameState.h"


class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Load();
	void PushState(GameState* gs);
	void PopState();
	void UpdateState(float timeDelta);
	void DrawState(sf::RenderWindow& window);

private:
	std::stack<GameState*> _states;
	Game* _game;
};
