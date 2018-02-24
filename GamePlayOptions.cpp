#include "stdafx.h"
#include "GamePlayOptions.h"


#pragma region GamePlayOptions

GamePlayOptions::GamePlayOptions(Game* g) : 
	binding(false), 
	playerNumber(1),
	controlPos(0) {
	_game = g;
	_settings = &(g->_settingsGameplay);
	CreateButtons();	
	LoadAudio();
}
GamePlayOptions::~GamePlayOptions() {
	_clickSound.resetBuffer();
}


void GamePlayOptions::LoadAudio() {
	if (_clickBuffer.loadFromFile("Audio\\click.wav"))
		std::cout << "\n_GamePlayOptions: Audio loaded";
	else return;
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(50);
	_clickSound.setPlayingOffset(sf::seconds(.15f));
}

void GamePlayOptions::Show() {
	LoadStrings();
	DrawButtons(_game->GetWindow());
	HandleEvents(_game->GetWindow());
}

void GamePlayOptions::CreateButtons() {
	MenuButton* _NTP1 = new MenuButton;
	MenuButton* _PTP1 = new MenuButton;
	MenuButton* _BCP1 = new MenuButton;
	MenuButton* _CP1  = new MenuButton;
	MenuButton* _NTP2 = new MenuButton;
	MenuButton* _PTP2 = new MenuButton;
	MenuButton* _BCP2 = new MenuButton;
	MenuButton* _CP2  = new MenuButton;
	MenuButton* _Play = new MenuButton;
	MenuButton* _Back = new MenuButton;

	sf::Font *f;
	f = &_game->_font;
	
	_NTP1->ac = NextTextureP1;
	_PTP1->ac = PrevTextureP1;
	_BCP1->ac = BindControlsP1;
	_CP1 ->ac = Nothing;
	_NTP2->ac = NextTextureP2;
	_PTP2->ac = PrevTextureP2;
	_BCP2->ac = BindControlsP2;
	_CP2 ->ac = Nothing;
	_Play->ac = Play;
	_Back->ac = Back;

	_NTP1->text.setFillColor(MenuFGColor);
	_PTP1->text.setFillColor(MenuFGColor);
	_BCP1->text.setFillColor(MenuFGColor);
	_CP1 ->text.setFillColor(MenuFGColor);
	_NTP2->text.setFillColor(MenuFGColor);
	_PTP2->text.setFillColor(MenuFGColor);
	_BCP2->text.setFillColor(MenuFGColor);
	_CP2 ->text.setFillColor(MenuFGColor);
	_Play->text.setFillColor(MenuFGColor);
	_Back->text.setFillColor(MenuFGColor);

	_NTP1->text.setFont(*f);
	_PTP1->text.setFont(*f);
	_BCP1->text.setFont(*f);
	_CP1 ->text.setFont(*f);
	_NTP2->text.setFont(*f);
	_PTP2->text.setFont(*f);
	_BCP2->text.setFont(*f);
	_CP2 ->text.setFont(*f);
	_Play->text.setFont(*f);
	_Back->text.setFont(*f);

	//_NTP1 ->text.setOrigin(_NTP1 ->text.getGlobalBounds().width / 2, _NTP1 ->text.getGlobalBounds().height / 2);
	//_PTP1 ->text.setOrigin(_PTP1 ->text.getGlobalBounds().width / 2, _PTP1 ->text.getGlobalBounds().height / 2);
	//_BCP1 ->text.setOrigin(_BCP1 ->text.getGlobalBounds().width / 2, _BCP1 ->text.getGlobalBounds().height / 2);
	//_CP1  ->text.setOrigin(_CP1  ->text.getGlobalBounds().width / 2, _CP1  ->text.getGlobalBounds().height / 2);
	//_NTP2 ->text.setOrigin(_NTP2 ->text.getGlobalBounds().width / 2, _NTP2 ->text.getGlobalBounds().height / 2);
	//_PTP2 ->text.setOrigin(_PTP2 ->text.getGlobalBounds().width / 2, _PTP2 ->text.getGlobalBounds().height / 2);
	//_BCP2 ->text.setOrigin(_BCP2 ->text.getGlobalBounds().width / 2, _BCP2 ->text.getGlobalBounds().height / 2);
	//_Play ->text.setOrigin(_Play ->text.getGlobalBounds().width / 2, _Play ->text.getGlobalBounds().height / 2);
	//_Back ->text.setOrigin(_Back ->text.getGlobalBounds().width / 2, _Back ->text.getGlobalBounds().height / 2);

	_buttons.push_back(_NTP1);
	_buttons.push_back(_PTP1);
	_buttons.push_back(_CP1);
	_buttons.push_back(_BCP1);
	_buttons.push_back(_NTP2);
	_buttons.push_back(_PTP2);
	_buttons.push_back(_CP2);
	_buttons.push_back(_BCP2);
	_buttons.push_back(_Play);
	_buttons.push_back(_Back);
}

void GetKeys(std::map<std::string, std::string> aux, std::vector<std::string> &key) {
	std::map<std::string, std::string>::iterator i;
	i = aux.find("Up");				if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Down");			if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Left");			if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Right");			if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Reflector Left"); if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Reflector Right");if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Action");			if (i != aux.end()) key.push_back(i->second);
}

void GamePlayOptions::LoadStrings() {
	std::vector<std::string> key; GetKeys(_settings->gControlsP1Text(), key);
	_buttons[0]->text.setString(">");
	_buttons[1]->text.setString("<");
	_buttons[2]->text.setString(
		"[Up]                 " + key[0] +
		"\n[Down]           \t" + key[1] +
		"\n[Left]           \t" + key[2] +
		"\n[Right]          \t" + key[3] +
		"\n[Reflector Left] \t" + key[4] +
		"\n[Reflector Right]\t" + key[5] +
		"\n[Action]         \t" + key[6]);
	_buttons[3]->text.setString("Rebind Controls");
	_buttons[4]->text.setString(">");
	_buttons[5]->text.setString("<");
	key.clear(); GetKeys(_settings->gControlsP2Text(), key);
	_buttons[6]->text.setString(
		"[Up]                 " + key[0] +
		"\n[Down]           \t" + key[1] +
		"\n[Left]           \t" + key[2] +
		"\n[Right]          \t" + key[3] +
		"\n[Reflector Left] \t" + key[4] +
		"\n[Reflector Right]\t" + key[5] +
		"\n[Action]         \t" + key[6]);
	_buttons[7]->text.setString("Rebind Controls");
	_buttons[8]->text.setString("Play");
	_buttons[9]->text.setString("Back");

	sf::Vector2u s = _game->GetWindow().getSize();
	for (int i = 0; i < _buttons.size(); i++) {
		_buttons[i]->text.setCharacterSize((int)(s.y / 24.5));
		_buttons[i]->text.setOrigin(_buttons[i]->text.getGlobalBounds().width / 2, _buttons[i]->text.getGlobalBounds().height / 2);
	}

	_Texture.loadFromFile("Images\\Players.png");
	_SpriteP1.setTexture(_Texture); 
	_SpriteP2.setTexture(_Texture);
	_SpriteP1.setTextureRect(sf::IntRect(_settings->gTextureP1() * 64, 0, 64, 64));
	_SpriteP2.setTextureRect(sf::IntRect(_settings->gTextureP2() * 64, 0, 64, 64));
	_SpriteP1.setOrigin(_SpriteP1.getGlobalBounds().width / 2, _SpriteP1.getGlobalBounds().height / 2);
	_SpriteP2.setOrigin(_SpriteP2.getGlobalBounds().width / 2, _SpriteP2.getGlobalBounds().height / 2);
	_SpriteP2.setScale(1.5f, 1.5f);
	_SpriteP1.setScale(1.5f, 1.5f);
	
	_SpriteP1.setPosition(s.x / 4 * 3, s.y / 10 * 2.5);
	_SpriteP2.setPosition(s.x / 4    , s.y / 10 * 2.5);
	for (int i = 2; i <= 3; i++) _buttons[i]->text.setPosition(s.x / 4 * 3, s.y / 10 * (i*3-1));
	for (int i = 6; i <= 7; i++) _buttons[i]->text.setPosition(s.x / 4    , s.y / 10 * (i*3-13));
	
	//_SpriteP1.setPosition(32, 32);

 	//_buttons[0]->text.setPosition(_SpriteP1.getPosition().x , _SpriteP1.getPosition().y);
	//_buttons[1]->text.setPosition(_SpriteP1.getPosition().x , _SpriteP1.getPosition().y);
	_buttons[0]->text.setPosition(_SpriteP1.getGlobalBounds().left + _SpriteP1.getGlobalBounds().width * 5 / 4, _SpriteP1.getGlobalBounds().top + _SpriteP1.getGlobalBounds().height / 2);
	_buttons[1]->text.setPosition(_SpriteP1.getGlobalBounds().left - _SpriteP1.getGlobalBounds().width	   / 4, _SpriteP1.getGlobalBounds().top + _SpriteP1.getGlobalBounds().height / 2);
	_buttons[4]->text.setPosition(_SpriteP2.getGlobalBounds().left + _SpriteP2.getGlobalBounds().width * 5 / 4, _SpriteP2.getGlobalBounds().top + _SpriteP2.getGlobalBounds().height / 2);
	_buttons[5]->text.setPosition(_SpriteP2.getGlobalBounds().left - _SpriteP2.getGlobalBounds().width	   / 4, _SpriteP2.getGlobalBounds().top + _SpriteP2.getGlobalBounds().height / 2);
	
	_buttons[8]->text.setPosition(s.x / 2, s.y - s.y / 15 * 2);
	_buttons[9]->text.setPosition(_buttons[8]->text.getPosition().x, _buttons[8]->text.getPosition().y + _buttons[8]->text.getGlobalBounds().height * 1.25f);
}

void GamePlayOptions::DrawButtons(sf::RenderWindow& window) {
	window.setView(window.getDefaultView());

	window.clear(MenuBGColor);

	window.draw(_SpriteP1); window.draw(_SpriteP2);
	for (int i = 0; i < _buttons.size(); i++)
		window.draw(_buttons[i]->text);

	window.display();
}

void GamePlayOptions::HandleEvents(sf::RenderWindow& window) {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (binding) {
			if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape) { 
					binding = false;
					_auxControls.clear();
					LoadStrings();
				}
				else {
					_auxControls.insert(std::pair<std::string, sf::Keyboard::Key>(_settings->controlNames[controlPos++], e.key.code));
				}
				if (_auxControls.size() == _settings->controlNames.size()) {
					if(playerNumber == 1) _settings->sControlsP1(_auxControls);
					else _settings->sControlsP2(_auxControls);
					binding = false;
					_auxControls.clear();
					LoadStrings();
				}
			}			
		}
		else {
			if (e.type == sf::Event::MouseButtonPressed)
				return HandleClicks(e.mouseButton.x, e.mouseButton.y);
			if (e.type == sf::Event::Closed)
				_game->Quit();
			if (e.type == sf::Event::KeyPressed &&
				e.key.code == sf::Keyboard::Escape)
				_game->PopState();
		}
	}
}

void GamePlayOptions::HandleClicks(int x, int y) {
	for (int i = 0; i < _buttons.size(); i++)
		if (_buttons[i]->text.getGlobalBounds().contains(x, y))
			switch (_buttons[i]->ac) {
			case Nothing:			break;
			case NextTextureP1:		_clickSound.play(); NTextureP1();  return;
			case PrevTextureP1:		_clickSound.play(); PTextureP1();  return;
			case NextTextureP2:		_clickSound.play(); NTextureP2();  return;
			case PrevTextureP2:		_clickSound.play(); PTextureP2();  return;
			case BindControlsP1:	_clickSound.play(); BControlsP1(); return;
			case BindControlsP2:	_clickSound.play(); BControlsP2(); return;
			case Play:				_clickSound.play(); _settings->Save(); _game->PushState(new GamePlay(_game)); return;
			case Back:				_clickSound.play(); _settings->Save(); _game->PopState(); return;
			default:				break;
			}
}

void GamePlayOptions::NTextureP1() {
	int aux = _settings->gTextureP1();
	if (aux == 6) aux = 0;
	else aux++;
	_settings->sTextureP1(aux);
	CreateButtons();
}

void GamePlayOptions::PTextureP1() {
	int aux = _settings->gTextureP1();
	if (aux == 0) aux = 6;
	else aux--;
	_settings->sTextureP1(aux);
	CreateButtons();
}

void GamePlayOptions::NTextureP2() {
	int aux = _settings->gTextureP2();
	if (aux == 6) aux = 1;
	else aux++;
	_settings->sTextureP2(aux);
	CreateButtons();
}

void GamePlayOptions::PTextureP2() {
	int aux = _settings->gTextureP2();
	if (aux == 0) aux = 6;
	else aux--;
	_settings->sTextureP2(aux);
	CreateButtons();
}

void GamePlayOptions::BControlsP1() {
	binding = true;
	controlPos = 0;
	playerNumber = 1;
}

void GamePlayOptions::BControlsP2() {
	binding = true;
	controlPos = 0;
	playerNumber = 2;
}

void GamePlayOptions::UpdateSettings() {
	_settings->Save();
	_game->LoadGame();
	//LoadWindow();
	//_score.Load(_settings->gResolution(), &internalClock);
}


#pragma endregion 
