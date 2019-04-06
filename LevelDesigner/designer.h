#pragma once
#include <SFML/Graphics.hpp>
class designer
{
	int cameraX;
	int cameraY;
	int totalX;
	int k;
	sf::RenderWindow *window;
	sf::View *camera;
	sf::Font font;
	sf::Texture *activeText;
	sf::Sprite *activeSprite;
	std::vector<sf::Texture> vectorTexture;
	std::vector<sf::Sprite> vectorSprite;
	std::vector<std::string> vectorFileName;
	std::vector<sf::RectangleShape> vectorButton;
	std::vector<sf::Text> vectorButtonText;

	bool spriteMove = false;
	bool LControl = false;
public:

	designer(int cameraX, int cameraY, int totalX);
	void createScreen();
	void ScreenEvent();

private:

	void drawGrid();
	void drawButton();
	void drawSprite(sf::RenderWindow *window);
	bool isMouseOnSprite(sf::RenderWindow *window, sf::Sprite *groundS);
	void scroolToGrid(sf::Sprite *ground);
	void printLevel();
	bool isMouseCliked(sf::RenderWindow *window, sf::RectangleShape *button);
};

