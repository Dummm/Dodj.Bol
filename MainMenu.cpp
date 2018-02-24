#include "stdafx.h"
#include "MainMenu.h"
#include "Options.h"
#include "GamePlayOptions.h"
#include "MultiplayerMenu.h"


#pragma region Main Menu

MainMenu::MainMenu(Game* g) {
	_game = g;
	CreateButtons();
	LoadAudio();
}
MainMenu::~MainMenu() {
	_clickSound.resetBuffer();
}

void MainMenu::LoadAudio() {
	if (_clickBuffer.loadFromFile("Audio\\click.wav"))
		std::cout << "\n_MainMenu: Audio loaded";
	else return;
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(50);
	_clickSound.setPlayingOffset(sf::seconds(.15f));
}

void MainMenu::Show() {
	LoadStrings();
	DrawButtons(_game->GetWindow());
	HandleEvents(_game->GetWindow());
}

void MainMenu::CreateButtons() {
	MenuButton* _Title		 = new MenuButton;
	MenuButton* _TitleShadow = new MenuButton;
	MenuButton* _JoinGame	 = new MenuButton;
	MenuButton* _CreateGame	 = new MenuButton;
	MenuButton* _Play		 = new MenuButton;
	MenuButton* _Options	 = new MenuButton;
	MenuButton* _Exit		 = new MenuButton;

	sf::Font *f, *fB;
	f =  &_game->_font;
	fB = &_game->_fontBold;
	
	_Title		->ac = Nothing;
	_TitleShadow->ac = Nothing;
	_JoinGame	->ac = JGame;
	_CreateGame	->ac = CGame;
	_Play		->ac = Play;
	_Options	->ac = Option;
	_Exit		->ac = Exit;

	_Title		->text.setString("[Dodj.Bol]");
	_TitleShadow->text.setString("[Dodj.Bol]");
	_JoinGame	->text.setString("Join Game");
	_CreateGame	->text.setString("Create Game");
	_Play		->text.setString("Play");
	_Options	->text.setString("Options");
	_Exit		->text.setString("Exit");

	_Title		->text.setFillColor(MenuFGColor);
	_TitleShadow->text.setFillColor(MenuSHColor);
	_Play		->text.setFillColor(MenuFGColor);
	_JoinGame	->text.setFillColor(MenuFGColor);
	_CreateGame	->text.setFillColor(MenuFGColor);
	_Options	->text.setFillColor(MenuFGColor);
	_Exit		->text.setFillColor(MenuFGColor);

	_Title		->text.setFont(*fB);
	_TitleShadow->text.setFont(*fB);
	_JoinGame	->text.setFont(*f);
	_CreateGame	->text.setFont(*f);
	_Play		->text.setFont(*f);
	_Options	->text.setFont(*f);
	_Exit		->text.setFont(*f);

	_buttons.push_back(_TitleShadow);
	_buttons.push_back(_Title);
	_buttons.push_back(_JoinGame);
	_buttons.push_back(_CreateGame);
	_buttons.push_back(_Play);
	_buttons.push_back(_Options);
	_buttons.push_back(_Exit);
}

void MainMenu::LoadStrings() {
	sf::Vector2u s = _game->GetWindow().getSize();
	
	_buttons[0]->text.setCharacterSize(s.y / 9);
	_buttons[1]->text.setCharacterSize(s.y / 9);
	_buttons[2]->text.setCharacterSize(s.y / 17);
	_buttons[3]->text.setCharacterSize(s.y / 17);
	_buttons[4]->text.setCharacterSize(s.y / 17);
	_buttons[5]->text.setCharacterSize(s.y / 17);
	_buttons[6]->text.setCharacterSize(s.y / 17);

	_buttons[0]->text.setPosition(s.x / 12, s.y / 6);
	_buttons[1]->text.setPosition(s.x / 12 + 5, s.y / 6 + 5);
	_buttons[2]->text.setPosition(s.x / 12, s.y / 12 * 6);
	_buttons[3]->text.setPosition(s.x / 12, s.y / 12 * 7);
	_buttons[4]->text.setPosition(s.x / 12, s.y / 12 * 8);
	_buttons[5]->text.setPosition(s.x / 12, s.y / 12 * 9);
	_buttons[6]->text.setPosition(s.x / 12, s.y / 12 * 10);
}

void MainMenu::DrawButtons(sf::RenderWindow& window) {
	window.setView(window.getDefaultView());

	window.clear(MenuBGColor);

	std::vector<MenuButton*>::iterator i;
	for (i = _buttons.begin(); i != _buttons.end(); i++)
		window.draw((*i)->text);

	window.display();
}

void MainMenu::HandleEvents(sf::RenderWindow& window) {
	sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::MouseButtonPressed)
				HandleClicks(e.mouseButton.x, e.mouseButton.y);
			if ((e.type == sf::Event::Closed) ||
				(e.type == sf::Event::KeyPressed &&
				e.key.code == sf::Keyboard::Escape))
				_game->Quit();
		}
}

void MainMenu::HandleClicks(int x, int y) {
	std::vector<MenuButton*>::iterator i;
	for (i = _buttons.begin(); i != _buttons.end(); i++)
		if ((*i)->text.getGlobalBounds().contains(x, y))
			switch ((*i)->ac)
			{
			case Nothing:	break;
			case CGame:		_clickSound.play(); _game->PushState(new MultiplayerMenu(_game));	return;
			case JGame:		_clickSound.play(); _game->PushState(new MultiplayerMenu(_game));	return;
			//case Play:		_game->PushState(new GamePlay(_game)); return;
			case Play:		_clickSound.play(); _game->PushState(new GamePlayOptions(_game));	return;
			case Option:	_clickSound.play(); _game->PushState(new Options(_game));			return;
			case Exit:		/*_clickSound.play();*/ _game->Quit();									return;
			default:		break;
			}
}

#pragma endregion Main Menu
