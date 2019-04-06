#include "firstSetting.h"
#include "firstSetting.h"
#include <SFML/Graphics.hpp>
#include <iostream>

firstSetting::firstSetting()
{
	// Setting Screen Size
	screenX = 400;
	screenY = 330;
	font.loadFromFile("arialn.TTF");
}

int * firstSetting::show()
{
	settingWindow = new sf::RenderWindow(sf::VideoMode(screenX, screenY), "New Designer Page Setting");

	while (settingWindow->isOpen()) {
		
		sf::String xInput;
		sf::Text xText;
		xText.setFont(font);
		xText.setFillColor(sf::Color::Black);
		xText.setCharacterSize(25);
		xText.setPosition(sf::Vector2f(110, 20));
		
		sf::String yInput;
		sf::Text yText;
		yText.setFont(font);
		yText.setFillColor(sf::Color::Black);
		yText.setCharacterSize(25);
		yText.setPosition(sf::Vector2f(110, 80));
		

		sf::String totalInput;
		sf::Text totalText;
		totalText.setFont(font);
		totalText.setFillColor(sf::Color::Black);
		totalText.setCharacterSize(25);
		totalText.setPosition(sf::Vector2f(160, 140));
	

		sf::Text sizeX;
		sizeX.setFont(font);
		sizeX.setFillColor(sf::Color::Black);
		sizeX.setCharacterSize(25);
		sizeX.setString("Size X :");
		sizeX.setPosition(sf::Vector2f(20, 20));

		sf::Text sizeY;
		sizeY.setFont(font);
		sizeY.setFillColor(sf::Color::Black);
		sizeY.setCharacterSize(25);
		sizeY.setString("Size Y :");
		sizeY.setPosition(sf::Vector2f(20, 80));

		sf::Text sizeTotal;
		sizeTotal.setFont(font);
		sizeTotal.setFillColor(sf::Color::Black);
		sizeTotal.setCharacterSize(25);
		sizeTotal.setString("Size Total X :");
		sizeTotal.setPosition(sf::Vector2f(20, 140));

		sf::RectangleShape textFieldX(sf::Vector2f(270, 50));
		textFieldX.setPosition(200, 40);
		textFieldX.setFillColor(sf::Color::White);
		textFieldX.setOrigin(sf::Vector2f(100, 25));

		sf::RectangleShape textFieldY(sf::Vector2f(270, 50));
		textFieldY.setPosition(200, 100);
		textFieldY.setFillColor(sf::Color::White);
		textFieldY.setOrigin(sf::Vector2f(100, 25));

		sf::RectangleShape textFieldTotal(sf::Vector2f(220, 50));
		textFieldTotal.setPosition(250, 160);
		textFieldTotal.setFillColor(sf::Color::White);
		textFieldTotal.setOrigin(sf::Vector2f(100, 25));

		sf::Text enterB;
		enterB.setFont(font);
		enterB.setFillColor(sf::Color::Black);
		enterB.setCharacterSize(25);
		enterB.setString("Enter");
		enterB.setPosition(sf::Vector2f(275, 240));

		sf::RectangleShape enterButton(sf::Vector2f(100.f, 80.f));
		enterButton.setPosition(300, 240);
		enterButton.setFillColor(sf::Color::White);
		enterButton.setOrigin(50, 25);

		std::vector<sf::RectangleShape> textFieldVector;
		textFieldVector.push_back(textFieldX);
		textFieldVector.push_back(textFieldY);
		textFieldVector.push_back(textFieldTotal);
		textFieldVector.push_back(enterButton);

		auto drawButText = [&]() {
			settingWindow->draw(sizeX);
			settingWindow->draw(sizeY);
			settingWindow->draw(sizeTotal);
			settingWindow->draw(textFieldX);
			settingWindow->draw(textFieldY);
			settingWindow->draw(textFieldTotal);
			settingWindow->draw(enterButton);
			settingWindow->draw(enterB);
			settingWindow->draw(xText);
			settingWindow->draw(yText);
			settingWindow->draw(totalText);
		
		};

		enum ýnputSelect { xField, yField, totalXField };
		ýnputSelect direc = xField;

		while (settingWindow->isOpen()) {
			sf::Event eventEdit;
			while (settingWindow->pollEvent(eventEdit)) {
				if (eventEdit.type == sf::Event::Closed) {
					exit(0);
				}
				if (eventEdit.type == sf::Event::MouseButtonPressed && eventEdit.mouseButton.button == sf::Mouse::Left) {
					bool clickEvent;
					for (int i = 0; i < textFieldVector.size(); i++) {
						clickEvent = isMouseCliked(settingWindow, &textFieldVector.at(i));
						if (clickEvent == true) {
							if (i == 0)
								direc = xField;
							else if (i == 1)
								direc = yField;
							else if (i == 2)
								direc = totalXField;
							else {
								
								settingArray[0] = std::atoi(xText.getString().toAnsiString().c_str());
								settingArray[1] = std::atoi(yText.getString().toAnsiString().c_str());
								settingArray[2] = std::atoi(totalText.getString().toAnsiString().c_str());
								settingWindow->close();

								/*std::cout << "FirstSetting X : " << settingArray[0];
								std::cout << "FirstSetting Y : " << settingArray[1];
								std::cout << "FirstSetting Total X : " << settingArray[2];*/
							}
							break;
						}
					}
				}
				if (eventEdit.type == sf::Event::TextEntered && eventEdit.text.unicode < 128)
				{
					if (eventEdit.text.unicode == 8) {
						if (direc == xField && xInput.getSize() != 0) {
							xInput.erase(xInput.getSize() - 1, 1);
						}
						else if (direc == yField && yInput.getSize() != 0) {
							yInput.erase(yInput.getSize() - 1, 1);
						}
						else if (direc == totalXField && totalInput.getSize() != 0) {
							totalInput.erase(totalInput.getSize() - 1, 1);
						}
					}
					else {
						if (direc == xField) {
							xInput += eventEdit.text.unicode;
						}
						else if (direc == yField) {
							yInput += eventEdit.text.unicode;
						}
						else if (direc == totalXField) {
							totalInput += eventEdit.text.unicode;
						}
					}
					xText.setString(xInput);
					yText.setString(yInput);
					totalText.setString(totalInput);
				}


			}

			settingWindow->clear(sf::Color(169, 169, 169));
			drawButText();
			settingWindow->display();
		}
	}

	return settingArray;
}

bool firstSetting::isMouseCliked(sf::RenderWindow * window, sf::RectangleShape * button)
{
	float mouseX = sf::Mouse::getPosition(*window).x;
	float mouseY = sf::Mouse::getPosition(*window).y;

	sf::Vector2f mouseXY = window->mapPixelToCoords(sf::Vector2i(mouseX, mouseY));

	float difX = mouseXY.x - button->getPosition().x;
	float difY = mouseXY.y - button->getPosition().y;

	if (difX < (button->getSize().x / 2) && difX > -(button->getSize().x / 2)
		&& difY < (button->getSize().y / 2) && difY > -(button->getSize().y / 2)) {
		return true;
	}

	return false;
}