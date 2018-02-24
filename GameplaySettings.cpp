#include "stdafx.h"
#include "GameplaySettings.h"


GameplaySettings::GameplaySettings() {
	controlNames.clear();
	controlNames.push_back("Up");
	controlNames.push_back("Down");
	controlNames.push_back("Left");
	controlNames.push_back("Right");
	controlNames.push_back("Reflector Left");
	controlNames.push_back("Reflector Right");
	controlNames.push_back("Action");
}
GameplaySettings::~GameplaySettings() {}

void GameplaySettings::Load(std::string location) {
	_settings.clear();
	_location = location;
	std::string aux;
	//char aux;
	_file.open(_location);

	_controlsP1.clear(); 
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Up", StringToKey(aux)));
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Down", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Left", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Right", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Reflector Left", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Reflector Right", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP1.insert(std::pair<std::string, sf::Keyboard::Key>("Action", StringToKey(aux)));
	
	_controlsP2.clear();
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Up", StringToKey(aux)));		
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Down", StringToKey(aux)));	
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Left", StringToKey(aux)));	
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Right", StringToKey(aux)));	
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Reflector Left", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Reflector Right", StringToKey(aux))); 
	_file >> aux; toupper(aux[0]); _controlsP2.insert(std::pair<std::string, sf::Keyboard::Key>("Action", StringToKey(aux)));

	_file >> aux; _settings.push_back(std::stoi(aux));
	_file >> aux; _settings.push_back(std::stoi(aux));

	/*while (std::getline(_file, aux))
		_settings.push_back(std::stoi(aux));*/
	_file.close();
	std::cout << "\n_GameplaySettings: Settings loaded.";
}

void GetKeys2(std::map<std::string, std::string> aux, std::vector<std::string> &key) {
	std::map<std::string, std::string>::iterator i;
	i = aux.find("Up");				if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Down");			if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Left");			if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Right");			if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Reflector Left"); if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Reflector Right");if (i != aux.end()) key.push_back(i->second);
	i = aux.find("Action");			if (i != aux.end()) key.push_back(i->second);
}

void GameplaySettings::Save() {
	_file.open(_location);

	std::vector<std::string> key; GetKeys2(gControlsP1Text(), key);
	for (int i = 0; i < key.size(); i++) _file << key[i] << " "; _file << "\n";
	key.clear(); GetKeys2(gControlsP2Text(), key);
	for (int i = 0; i < key.size(); i++) _file << key[i] << " "; _file << "\n";

	for (int i = 0; i < _settings.size(); i++) {
		_file << _settings[i];
		if (i < _settings.size() - 1) _file << "\n";
	}
	_file.close();
	std::cout << "\n_GameplaySettings: Settings saved.";
	Load(_location);
}

int  GameplaySettings::gSettingByIndex(int i) {
	return _settings[i];
}
void GameplaySettings::sSettingByIndex(int i, int val) {
	_settings[i] = val;
}

std::map<std::string, sf::Keyboard::Key> GameplaySettings::gControlsP1() {
	return _controlsP1;
}
void GameplaySettings::sControlsP1(std::map<std::string, sf::Keyboard::Key> _ctrls) {
	_controlsP1 = _ctrls;
}

std::map<std::string, sf::Keyboard::Key> GameplaySettings::gControlsP2() {
	return _controlsP2;
}
void GameplaySettings::sControlsP2(std::map<std::string, sf::Keyboard::Key> _ctrls) {
	_controlsP2 = _ctrls;
}

int	 GameplaySettings::gTextureP1() {
	return _settings[0];
}
void GameplaySettings::sTextureP1(int i) {
	_settings[0] = i;
}

int  GameplaySettings::gTextureP2() {
	return _settings[1];
}
void GameplaySettings::sTextureP2(int i) {
	_settings[1] = i;
}

sf::Keyboard::Key GameplaySettings::StringToKey(std::string s) {
	if(s == "Unknown") return 		sf::Keyboard::Unknown;
	if(s == "A") return 			sf::Keyboard::A;		
	if(s == "B") return 			sf::Keyboard::B;		
	if(s == "C") return 			sf::Keyboard::C;		
	if(s == "D") return 			sf::Keyboard::D;		
	if(s == "E") return 			sf::Keyboard::E;		
	if(s == "F") return 			sf::Keyboard::F;		
	if(s == "G") return 			sf::Keyboard::G;		
	if(s == "H") return 			sf::Keyboard::H;		
	if(s == "I") return 			sf::Keyboard::I;		
	if(s == "J") return 			sf::Keyboard::J;		
	if(s == "K") return 			sf::Keyboard::K;		
	if(s == "L") return 			sf::Keyboard::L;		
	if(s == "M") return 			sf::Keyboard::M;		
	if(s == "N") return 			sf::Keyboard::N;		
	if(s == "O") return 			sf::Keyboard::O;		
	if(s == "P") return 			sf::Keyboard::P;		
	if(s == "Q") return 			sf::Keyboard::Q;		
	if(s == "R") return 			sf::Keyboard::R;		
	if(s == "S") return 			sf::Keyboard::S;		
	if(s == "T") return 			sf::Keyboard::T;		
	if(s == "U") return 			sf::Keyboard::U;		
	if(s == "V") return 			sf::Keyboard::V;		
	if(s == "W") return 			sf::Keyboard::W;		
	if(s == "X") return 			sf::Keyboard::X;		
	if(s == "Y") return 			sf::Keyboard::Y;		
	if(s == "Z") return 			sf::Keyboard::Z;		
	if(s == "Num0") return 			sf::Keyboard::Num0;	
	if(s == "Num1") return 			sf::Keyboard::Num1;	
	if(s == "Num2") return 			sf::Keyboard::Num2;	
	if(s == "Num3") return 			sf::Keyboard::Num3;	
	if(s == "Num4") return 			sf::Keyboard::Num4;	
	if(s == "Num5") return 			sf::Keyboard::Num5;	
	if(s == "Num6") return 			sf::Keyboard::Num6;	
	if(s == "Num7") return 			sf::Keyboard::Num7;	
	if(s == "Num8") return 			sf::Keyboard::Num8;	
	if(s == "Num9") return 			sf::Keyboard::Num9;	
	if(s == "Escape") return 		sf::Keyboard::Escape;
	if(s == "LControl") return 		sf::Keyboard::LControl;
	if(s == "LShift") return 		sf::Keyboard::LShift;
	if(s == "LAlt") return 			sf::Keyboard::LAlt;
	if(s == "LSystem") return 		sf::Keyboard::LSystem;
	if(s == "RControl") return 		sf::Keyboard::RControl;
	if(s == "RShift") return 		sf::Keyboard::RShift;
	if(s == "RAlt") return 			sf::Keyboard::RAlt;
	if(s == "RSystem") return 		sf::Keyboard::RSystem;
	if(s == "Menu") return 			sf::Keyboard::Menu;
	if(s == "LBracket") return 		sf::Keyboard::LBracket;
	if(s == "RBracket") return 		sf::Keyboard::RBracket;
	if(s == "SemiColon") return 	sf::Keyboard::SemiColon;
	if(s == "Comma") return 		sf::Keyboard::Comma;
	if(s == "Period") return 		sf::Keyboard::Period;
	if(s == "Quote") return 		sf::Keyboard::Quote;
	if(s == "Slash") return 		sf::Keyboard::Slash;
	if(s == "BackSlash") return 	sf::Keyboard::BackSlash;
	if(s == "Tilde") return 		sf::Keyboard::Tilde;
	if(s == "Equal") return 		sf::Keyboard::Equal;
	if(s == "Dash") return 			sf::Keyboard::Dash;
	if(s == "Space") return 		sf::Keyboard::Space;
	if(s == "Return") return 		sf::Keyboard::Return;
	if(s == "BackSpace") return 	sf::Keyboard::BackSlash;
	if(s == "Tab") return 			sf::Keyboard::Tab;
	if(s == "PageUp") return 		sf::Keyboard::PageUp;
	if(s == "PageDown") return 		sf::Keyboard::PageDown;
	if(s == "End") return 			sf::Keyboard::End;
	if(s == "Home") return 			sf::Keyboard::Home;
	if(s == "Insert") return 		sf::Keyboard::Insert;
	if(s == "Delete") return 		sf::Keyboard::Delete;
	if(s == "Add") return 			sf::Keyboard::Add;
	if(s == "Subtract") return 		sf::Keyboard::Subtract;
	if(s == "Multiply") return 		sf::Keyboard::Multiply;
	if(s == "Divide") return 		sf::Keyboard::Divide;
	if(s == "Left") return 			sf::Keyboard::Left;
	if(s == "Right") return 		sf::Keyboard::Right;
	if(s == "Up") return 			sf::Keyboard::Up;
	if(s == "Down") return 			sf::Keyboard::Down;
	if(s == "Numpad0") return 		sf::Keyboard::Numpad0;
	if(s == "Numpad1") return 		sf::Keyboard::Numpad1;
	if(s == "Numpad2") return 		sf::Keyboard::Numpad2;
	if(s == "Numpad3") return 		sf::Keyboard::Numpad3;
	if(s == "Numpad4") return 		sf::Keyboard::Numpad4;
	if(s == "Numpad5") return 		sf::Keyboard::Numpad5;
	if(s == "Numpad6") return 		sf::Keyboard::Numpad6;
	if(s == "Numpad7") return 		sf::Keyboard::Numpad7;
	if(s == "Numpad8") return 		sf::Keyboard::Numpad8;
	if(s == "Numpad9") return 		sf::Keyboard::Numpad9;
	if(s == "F1") return 			sf::Keyboard::F1;
	if(s == "F2") return 			sf::Keyboard::F2;
	if(s == "F3") return 			sf::Keyboard::F3;
	if(s == "F4") return 			sf::Keyboard::F4;
	if(s == "F5") return 			sf::Keyboard::F5;
	if(s == "F6") return 			sf::Keyboard::F6;
	if(s == "F7") return 			sf::Keyboard::F7;
	if(s == "F8") return 			sf::Keyboard::F8;
	if(s == "F9") return 			sf::Keyboard::F9;
	if(s == "F10") return 			sf::Keyboard::F10;
	if(s == "F11") return 			sf::Keyboard::F11;
	if(s == "F12") return 			sf::Keyboard::F12;
	if(s == "F13") return 			sf::Keyboard::F13;
	if(s == "F14") return 			sf::Keyboard::F14;
	if(s == "F15") return 			sf::Keyboard::F15;
	if(s == "Pause") return 		sf::Keyboard::Pause;
	if(s == "KeyCount") return 		sf::Keyboard::KeyCount;
}
std::string GameplaySettings::KeyToString(sf::Keyboard::Key k) {
	switch (k)
	{
	case sf::Keyboard::Unknown:		return "Unknown";		break;
	case sf::Keyboard::A:			return "A";				break;
	case sf::Keyboard::B:			return "B";				break;
	case sf::Keyboard::C:			return "C";				break;
	case sf::Keyboard::D:			return "D";				break;
	case sf::Keyboard::E:			return "E";				break;
	case sf::Keyboard::F:			return "F";				break;
	case sf::Keyboard::G:			return "G";				break;
	case sf::Keyboard::H:			return "H";				break;
	case sf::Keyboard::I:			return "I";				break;
	case sf::Keyboard::J:			return "J";				break;
	case sf::Keyboard::K:			return "K";				break;
	case sf::Keyboard::L:			return "L";				break;
	case sf::Keyboard::M:			return "M";				break;
	case sf::Keyboard::N:			return "N";				break;
	case sf::Keyboard::O:			return "O";				break;
	case sf::Keyboard::P:			return "P";				break;
	case sf::Keyboard::Q:			return "Q";				break;
	case sf::Keyboard::R:			return "R";				break;
	case sf::Keyboard::S:			return "S";				break;
	case sf::Keyboard::T:			return "T";				break;
	case sf::Keyboard::U:			return "U";				break;
	case sf::Keyboard::V:			return "V";				break;
	case sf::Keyboard::W:			return "W";				break;
	case sf::Keyboard::X:			return "X";				break;
	case sf::Keyboard::Y:			return "Y";				break;
	case sf::Keyboard::Z:			return "Z";				break;
	case sf::Keyboard::Num0:		return "Num0";			break;
	case sf::Keyboard::Num1:		return "Num1";			break;
	case sf::Keyboard::Num2:		return "Num2";			break;
	case sf::Keyboard::Num3:		return "Num3";			break;
	case sf::Keyboard::Num4:		return "Num4";			break;
	case sf::Keyboard::Num5:		return "Num5";			break;
	case sf::Keyboard::Num6:		return "Num6";			break;
	case sf::Keyboard::Num7:		return "Num7";			break;
	case sf::Keyboard::Num8:		return "Num8";			break;
	case sf::Keyboard::Num9:		return "Num9";			break;
	case sf::Keyboard::Escape:		return "Escape";		break;
	case sf::Keyboard::LControl:	return "LControl";		break;
	case sf::Keyboard::LShift:		return "LShift";		break;
	case sf::Keyboard::LAlt:		return "LAlt";			break;
	case sf::Keyboard::LSystem:		return "LSystem";		break;
	case sf::Keyboard::RControl:	return "RControl";		break;
	case sf::Keyboard::RShift:		return "RShift";		break;
	case sf::Keyboard::RAlt:		return "RAlt";			break;
	case sf::Keyboard::RSystem:		return "RSystem";		break;
	case sf::Keyboard::Menu:		return "Menu";			break;
	case sf::Keyboard::LBracket:	return "LBracket";		break;
	case sf::Keyboard::RBracket:	return "RBracket";		break;
	case sf::Keyboard::SemiColon:	return "SemiColon";		break;
	case sf::Keyboard::Comma:		return "Comma";			break;
	case sf::Keyboard::Period:		return "Period";		break;
	case sf::Keyboard::Quote:		return "Quote";			break;
	case sf::Keyboard::Slash:		return "Slash";			break;
	case sf::Keyboard::BackSlash:	return "BackSlash";		break;
	case sf::Keyboard::Tilde:		return "Tilde";			break;
	case sf::Keyboard::Equal:		return "Equal";			break;
	case sf::Keyboard::Dash:		return "Dash";			break;
	case sf::Keyboard::Space:		return "Space";			break;
	case sf::Keyboard::Return:		return "Return";		break;
	case sf::Keyboard::BackSpace:	return "BackSpace";		break;
	case sf::Keyboard::Tab:			return "Tab";			break;
	case sf::Keyboard::PageUp:		return "PageUp";		break;
	case sf::Keyboard::PageDown:	return "PageDown";		break;
	case sf::Keyboard::End:			return "End";			break;
	case sf::Keyboard::Home:		return "Home";			break;
	case sf::Keyboard::Insert:		return "Insert";		break;
	case sf::Keyboard::Delete:		return "Delete";		break;
	case sf::Keyboard::Add:			return "Add";			break;
	case sf::Keyboard::Subtract:	return "Subtract";		break;
	case sf::Keyboard::Multiply:	return "Multiply";		break;
	case sf::Keyboard::Divide:		return "Divide";		break;
	case sf::Keyboard::Left:		return "Left";			break;
	case sf::Keyboard::Right:		return "Right";			break;
	case sf::Keyboard::Up:			return "Up";			break;
	case sf::Keyboard::Down:		return "Down";			break;
	case sf::Keyboard::Numpad0:		return "Numpad0";		break;
	case sf::Keyboard::Numpad1:		return "Numpad1";		break;
	case sf::Keyboard::Numpad2:		return "Numpad2";		break;
	case sf::Keyboard::Numpad3:		return "Numpad3";		break;
	case sf::Keyboard::Numpad4:		return "Numpad4";		break;
	case sf::Keyboard::Numpad5:		return "Numpad5";		break;
	case sf::Keyboard::Numpad6:		return "Numpad6";		break;
	case sf::Keyboard::Numpad7:		return "Numpad7";		break;
	case sf::Keyboard::Numpad8:		return "Numpad8";		break;
	case sf::Keyboard::Numpad9:		return "Numpad9";		break;
	case sf::Keyboard::F1:			return "F1";			break;
	case sf::Keyboard::F2:			return "F2";			break;
	case sf::Keyboard::F3:			return "F3";			break;
	case sf::Keyboard::F4:			return "F4";			break;
	case sf::Keyboard::F5:			return "F5";			break;
	case sf::Keyboard::F6:			return "F6";			break;
	case sf::Keyboard::F7:			return "F7";			break;
	case sf::Keyboard::F8:			return "F8";			break;
	case sf::Keyboard::F9:			return "F9";			break;
	case sf::Keyboard::F10:			return "F10";			break;
	case sf::Keyboard::F11:			return "F11";			break;
	case sf::Keyboard::F12:			return "F12";			break;
	case sf::Keyboard::F13:			return "F13";			break;
	case sf::Keyboard::F14:			return "F14";			break;
	case sf::Keyboard::F15:			return "F15";			break;
	case sf::Keyboard::Pause:		return "Pause";			break;
	case sf::Keyboard::KeyCount:	return "KeyCount";		break;
	default:												break;
	}
}

std::map<std::string, std::string> GameplaySettings::gControlsP1Text() {
	std::map<std::string, std::string> _aux;
	std::map<std::string, sf::Keyboard::Key>::iterator i;
	for (i = _controlsP1.begin(); i != _controlsP1.end(); i++) {
		_aux.insert(std::pair<std::string, std::string>(i->first, KeyToString(i->second)));
	}
	return _aux;
}
std::map<std::string, std::string> GameplaySettings::gControlsP2Text() {
	std::map<std::string, std::string> _aux;
	std::map<std::string, sf::Keyboard::Key>::iterator i;
	for (i = _controlsP2.begin(); i != _controlsP2.end(); i++) {
		_aux.insert(std::pair<std::string, std::string>(i->first, KeyToString(i->second)));
	}
	return _aux;
}