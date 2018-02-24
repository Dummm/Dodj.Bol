#include "stdafx.h"
#include "GameStateManager.h"


GameStateManager::GameStateManager() {}
GameStateManager::~GameStateManager() {}

void GameStateManager::PushState(GameState* gs) {
	_states.push(gs);
}

void GameStateManager::PopState() {
	if (_states.empty()) return;
	delete _states.top();
	_states.pop();
}

void GameStateManager::UpdateState(float timeDelta) {
	if (_states.empty()) return;
	_states.top()->Update();
}

void GameStateManager::DrawState(sf::RenderWindow& window) {
	if (_states.empty()) return;
	_states.top()->Draw(window);
}