#pragma once


class GameSettings
{
public:
	GameSettings();
	~GameSettings();

	void Load(std::string location);
	void Save();

	int  gSettingByIndex(int i);
	void sSettingByIndex(int i, int val);

	int  gFullscreen();
	void sFullscreen(int val);

	sf::Vector2f gResolution();
	void		 sResolution(sf::Vector2f val);

	int  gAntialiasing();
	void sAntialiasing(int val);

	int  gVSync();
	void sVSync(int val);


private:
	std::fstream _file;
	std::string _location;
	std::vector<int> _settings;
};

