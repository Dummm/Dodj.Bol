#include "stdafx.h"
#include "Options.h"


#pragma region Options

Options::Options(Game* g) {
	_game = g;
	_settings = &(g->_settings);
	CreateButtons();
	LoadAudio();
}
Options::~Options() {
	_clickSound.resetBuffer();
}

void Options::LoadAudio() {
	if (_clickBuffer.loadFromFile("Audio\\click.wav"))
		std::cout << "\n_Options: Audio loaded";
	else return;
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(50);
	_clickSound.setPlayingOffset(sf::seconds(.15f));
}

void Options::Show() {
	LoadStrings();
	DrawButtons(_game->GetWindow());
	HandleEvents(_game->GetWindow());
}

void Options::CreateButtons() {
	MenuButton* _Fullscreen = new MenuButton;
	MenuButton* _Resolution = new MenuButton;
	MenuButton* _Antialiasing = new MenuButton;
	MenuButton* _VSync = new MenuButton;
	MenuButton* _Apply = new MenuButton;
	MenuButton* _Back = new MenuButton;

	sf::Font *f;
	f = &_game->_font;
	
	_Fullscreen->ac = Fullscreen;
	_Resolution->ac = Resolution;
	_Antialiasing->ac = Antialiasing;
	_VSync->ac = VSync;
	_Apply->ac = Apply;
	_Back->ac = Back;

	_Fullscreen->	text.setFillColor(MenuFGColor);
	_Resolution->	text.setFillColor(MenuFGColor);
	_Antialiasing->	text.setFillColor(MenuFGColor);
	_VSync->		text.setFillColor(MenuFGColor);
	_Apply->		text.setFillColor(MenuFGColor);
	_Back->			text.setFillColor(MenuFGColor);

	_Fullscreen->text.setFont(*f);
	_Resolution->text.setFont(*f);
	_Antialiasing->text.setFont(*f);
	_VSync->text.setFont(*f);
	_Apply->text.setFont(*f);
	_Back->text.setFont(*f);

	_buttons.push_back(_Fullscreen);
	_buttons.push_back(_Resolution);
	_buttons.push_back(_Antialiasing);
	_buttons.push_back(_VSync);
	_buttons.push_back(_Apply);
	_buttons.push_back(_Back);
}

void Options::LoadStrings() {
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

void Options::DrawButtons(sf::RenderWindow& window) {
	window.setView(window.getDefaultView());

	window.clear(MenuBGColor);

	for (int i = 0; i < _buttons.size(); i++)
		window.draw(_buttons[i]->text);

	window.display();
}

void Options::HandleEvents(sf::RenderWindow& window) {
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

void Options::HandleClicks(int x, int y) {
	for (int i = 0; i < _buttons.size(); i++)
		if (_buttons[i]->text.getGlobalBounds().contains(x, y))
			switch (_buttons[i]->ac) {
			case Nothing:		break;
			case Fullscreen:	_clickSound.play(); ToggleFullscreen();		return;
			case Resolution:	_clickSound.play(); ChangeResolution();		return;
			case Antialiasing:	_clickSound.play(); ChangeAntialiasing();	return;
			case VSync:			_clickSound.play(); ToggleVSync();			return;
			case Apply:			/*_clickSound.play();*/ SaveSettings();			return;
			case Back:			_clickSound.play(); _game->PopState();		return;
			default:			break;
			}
}

void Options::ToggleFullscreen() {
	_settings->sFullscreen(_settings->gFullscreen() == 1 ? 0 : 1);
}

void Options::ChangeResolution() {
		 if (_settings->gResolution() == sf::Vector2f( 800, 600))	 
			 _settings->sResolution(	 sf::Vector2f(1024, 768));
	else if (_settings->gResolution() == sf::Vector2f(1024, 768)) 
			 _settings->sResolution(	 sf::Vector2f(1280, 720));
	else if (_settings->gResolution() == sf::Vector2f(1280, 720))
			 _settings->sResolution(	 sf::Vector2f(1366, 768));
	else	 _settings->sResolution(	 sf::Vector2f( 800, 600));
}

void Options::ChangeAntialiasing() {
	_settings->sAntialiasing(
		(_settings->gAntialiasing() == 8) ? 0 : (_settings->gAntialiasing() + 1));
}

void Options::ToggleVSync() {
	_settings->sVSync(_settings->gVSync() == 1 ? 0 : 1);
}

void Options::SaveSettings() {
	_settings->Save();
	_game->LoadGame();
	//LoadWindow();
	//_score.Load(_settings->gResolution(), &internalClock);
}


#pragma endregion Options
