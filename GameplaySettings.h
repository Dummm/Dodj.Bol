#pragma once


class GameplaySettings
{
public:
	GameplaySettings();
	~GameplaySettings();

	std::vector<std::string> controlNames;

	void Load(std::string location);
	void Save();
	
	int  gSettingByIndex(int i);
	void sSettingByIndex(int i, int val);

	std::map<std::string, std::string> gControlsP1Text();
	std::map<std::string, sf::Keyboard::Key> gControlsP1();
	void sControlsP1(std::map<std::string, sf::Keyboard::Key> _ctrls);

	std::map<std::string, std::string> gControlsP2Text();
	std::map<std::string, sf::Keyboard::Key> gControlsP2();
	void sControlsP2(std::map<std::string, sf::Keyboard::Key> _ctrls);

	int	 gTextureP1();
	void sTextureP1(int i);

	int  gTextureP2();
	void sTextureP2(int i);

private:
	sf::Keyboard::Key StringToKey(std::string s);
	std::string KeyToString(sf::Keyboard::Key k);

	std::fstream _file;
	std::string _location;
	std::vector<int> _settings;
	std::map<std::string, sf::Keyboard::Key> _controlsP1;
	std::map<std::string, sf::Keyboard::Key> _controlsP2;
};

