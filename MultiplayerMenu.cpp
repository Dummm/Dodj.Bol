#include "stdafx.h"
#include "MultiplayerMenu.h"

MultiplayerMenu::MultiplayerMenu(Game* g) {
	_game = g;
	_settings = &(g->_settings);
	CreateButtons();
	LoadAudio();
}
MultiplayerMenu::~MultiplayerMenu() {
	_clickSound.resetBuffer();
}


void MultiplayerMenu::LoadAudio() {
	if (_clickBuffer.loadFromFile("Audio\\click.wav"))
		std::cout << "\n_MultiplayerMenu: Audio loaded";
	else return;
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(50);
	_clickSound.setPlayingOffset(sf::seconds(.15f));
}

void MultiplayerMenu::Show() {
	LoadStrings();
	DrawButtons(_game->GetWindow());
	HandleEvents(_game->GetWindow());
}

void MultiplayerMenu::CreateButtons() {
	MenuButton* _IP		 = new MenuButton;
	MenuButton* _AddIP	 = new MenuButton;
	MenuButton* _Connect = new MenuButton;
	MenuButton* _Back	 = new MenuButton;

	sf::Font *f;
	f = &_game->_font;
	
	_IP		->ac = IP;
	_AddIP	->ac = AddIP;
	_Connect->ac = Connect;
	_Back   ->ac = Back;

	_IP		 ->text.setFillColor(MenuFGColor);
	_AddIP	 ->text.setFillColor(MenuFGColor);
	_Connect ->text.setFillColor(MenuFGColor);
	_Back	 ->text.setFillColor(MenuFGColor);

	_IP		 ->text.setFont(*f);
	_AddIP	 ->text.setFont(*f);
	_Connect ->text.setFont(*f);
	_Back->text.setFont(*f);

	_buttons.push_back(_IP);
	_buttons.push_back(_AddIP);
	_buttons.push_back(_Connect);
	_buttons.push_back(_Back);
}

void MultiplayerMenu::LoadStrings() {
	std::string aux = (_settings->gFullscreen() == 1) ? "[Enabled]" : "[Disabled]";
	_buttons[0]->text.setString("Fullscreen " + aux);
	_buttons[1]->text.setString("Resolution [" +
		std::to_string((int)_settings->gResolution().x) + "x" +
		std::to_string((int)_settings->gResolution().y) + "]");
	_buttons[2]->text.setString("Antialiasing Level [" +
		std::to_string((int)_settings->gAntialiasing()) + "]");
	aux = (_settings->gVSync() == 1) ? "[Enabled]" : "[Disabled]";
	_buttons[3]->text.setString("V-Sync " + aux);
	_buttons[4]->text.setString("Apply");
	_buttons[5]->text.setString("Back");

	int nr = 3;
	sf::Vector2u s = _game->GetWindow().getSize();
	for (int i = 0; i < _buttons.size(); i++) {
		_buttons[i]->text.setOrigin(_buttons[i]->text.getGlobalBounds().width / 2, _buttons[i]->text.getGlobalBounds().height / 2);
		_buttons[i]->text.setCharacterSize(s.y / 15);
		_buttons[i]->text.setPosition(s.x / 2, s.y / 10 * (nr++));
	}
}

void MultiplayerMenu::DrawButtons(sf::RenderWindow& window) {
	window.setView(window.getDefaultView());

	window.clear(MenuBGColor);

	for (int i = 0; i < _buttons.size(); i++)
		window.draw(_buttons[i]->text);

	window.display();
}

void MultiplayerMenu::HandleEvents(sf::RenderWindow& window) {
	sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::MouseButtonPressed)
				return HandleClicks(e.mouseButton.x, e.mouseButton.y);
			if (e.type == sf::Event::Closed)
				_game->Quit();
			if (e.type == sf::Event::KeyPressed &&
				e.key.code == sf::Keyboard::Escape)
				_game->PopState();
		}
}

void MultiplayerMenu::HandleClicks(int x, int y) {
	for (int i = 0; i < _buttons.size(); i++)
		if (_buttons[i]->text.getGlobalBounds().contains(x, y))
			switch (_buttons[i]->ac) {
			case Nothing:		break;
			case IP:			_clickSound.play(); return;
			case AddIP:			_clickSound.play(); return;
			case Connect:		_clickSound.play(); return;
			case Back:			_clickSound.play(); _game->PopState();		return;
			default:			break;
			}
}
