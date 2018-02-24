#pragma once
#include "GameState.h"
#include "Game.h"

class Game;
class GameplaySettings;

class GamePlayOptions : public GameState {
public:
	GamePlayOptions(Game* g);
	~GamePlayOptions();

	void Show();

private:
	enum Action {
		Nothing,
		NextTextureP1,
		PrevTextureP1,
		NextTextureP2,
		PrevTextureP2,
		BindControlsP1,
		BindControlsP2,
		Play,
		Back
	};
	struct MenuButton {
	public:
		sf::Text text;
		Action ac;
	};
	std::vector<MenuButton*> _buttons;
	Game* _game;
	GameplaySettings* _settings;

	sf::Sprite _SpriteP1;
	sf::Sprite _SpriteP2;
	sf::Texture _Texture;

	sf::SoundBuffer _clickBuffer;
	sf::Sound _clickSound;
	
	bool binding;
	int playerNumber;
	int controlPos;
	std::map<std::string, sf::Keyboard::Key> _auxControls;

	void NTextureP1();
	void PTextureP1();
	void NTextureP2();
	void PTextureP2();
	void BControlsP1();
	void BControlsP2();

	void LoadAudio();
	void CreateButtons();
	void LoadStrings();
	void DrawButtons(sf::RenderWindow& window);
	void HandleEvents(sf::RenderWindow& window);
	void HandleClicks(int x, int y);

	void UpdateSettings();
};
