#pragma once
#include <SFML/Graphics.hpp>

class firstSetting
{
private:
	int screenX;
	int screenY;
	int settingArray[3];
	sf::RenderWindow *settingWindow;
	sf::Font font;
public:
	firstSetting();
	bool isMouseCliked(sf::RenderWindow * window, sf::RectangleShape * button);
	int* show();
};

