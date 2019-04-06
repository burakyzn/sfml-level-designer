#include "designer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

designer::designer(int settingArray[])
{
	this->cameraX = settingArray[0];
	this->cameraY = settingArray[1];
	this->totalX = settingArray[2];
	k = 0;

	/*std::cout << "Designer X : " << settingArray[0];
	std::cout << "Designer Y : " << settingArray[1];
	std::cout << "Designer Total X : " << settingArray[2];*/
}

void designer::createScreen()
{
	window = new sf::RenderWindow(sf::VideoMode(cameraX, cameraY), "Level Designer");
	camera = new sf::View(sf::Vector2f(cameraX / 2, cameraY / 2), sf::Vector2f(cameraX, cameraY));
	font.loadFromFile("arialn.TTF");
	drawGrid();
	drawButton();

	spriteMove = false;
	LControl = false;

}

void designer::drawGrid()
{
	for (int i = 0; i < cameraY; i += 25) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, 25 + i);
		lines[0].color = sf::Color::Black;
		lines[1].position = sf::Vector2f(totalX, 25 + i);
		lines[1].color = sf::Color::Black;
		window->draw(lines);
	}

	for (int i = 0; i < totalX; i += 25) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(25 + i, 0);
		lines[0].color = sf::Color::Black;
		lines[1].position = sf::Vector2f(25 + i, cameraY);
		lines[1].color = sf::Color::Black;
		window->draw(lines);
	}
}

void designer::drawButton()
{
	sf::Text rightDir;
	rightDir.setFont(font);
	rightDir.setFillColor(sf::Color::Black);
	rightDir.setCharacterSize(25);
	rightDir.setString("Right");
	rightDir.setPosition(sf::Vector2f(cameraX - 85, cameraY - 65));

	sf::RectangleShape rightDirButton(sf::Vector2f(75.f, 50.f));
	rightDirButton.setPosition(cameraX - 50, cameraY - 50);
	rightDirButton.setFillColor(sf::Color(169, 169, 169));
	rightDirButton.setOrigin(50, 25);

	sf::Text leftDir;
	leftDir.setFont(font);
	leftDir.setFillColor(sf::Color::Black);
	leftDir.setCharacterSize(25);
	leftDir.setString("Left");
	leftDir.setPosition(sf::Vector2f(45, cameraY - 65));

	sf::RectangleShape leftDirButton(sf::Vector2f(75.f, 50.f));
	leftDirButton.setPosition(75, cameraY - 50);
	leftDirButton.setFillColor(sf::Color(169, 169, 169));
	leftDirButton.setOrigin(50, 25);

	vectorButtonText.push_back(leftDir);
	vectorButtonText.push_back(rightDir);
	vectorButton.push_back(leftDirButton);
	vectorButton.push_back(rightDirButton);

	window->draw(vectorButton.at(0));
	window->draw(vectorButton.at(1));
	window->draw(vectorButtonText.at(0));
	window->draw(vectorButtonText.at(1));
}

void designer::ScreenEvent()
{
	while (window->isOpen()) {
		sf::Event eventMain;

		while (window->pollEvent(eventMain))
		{
			if (eventMain.type == sf::Event::Closed) {
				exit(0);
			}
			if (eventMain.type == sf::Event::MouseButtonPressed && eventMain.mouseButton.button == sf::Mouse::Left) {
				bool mouseOnSprite;
				for (k = 0; k < vectorSprite.size(); k++) {
					mouseOnSprite = isMouseOnSprite(window, &vectorSprite.at(k));
					if (mouseOnSprite == true) {
						spriteMove = true;
						break;
					}
				}

				if (LControl == false) {
					for (int i = 0; i < vectorButton.size(); i++) {
						bool mouseOnButton;
						mouseOnButton = isMouseCliked(window, &vectorButton.at(i));
						if (mouseOnButton == true) {
							if (i == 0) {
								if (camera->getCenter().x != cameraX / 2) {
									camera->setCenter(sf::Vector2f(float(camera->getCenter().x - 50), float(camera->getCenter().y)));
									vectorButtonText.at(0).setPosition(sf::Vector2f(vectorButtonText.at(0).getPosition().x - 50, vectorButtonText.at(0).getPosition().y));
									vectorButtonText.at(1).setPosition(sf::Vector2f(vectorButtonText.at(1).getPosition().x - 50, vectorButtonText.at(1).getPosition().y));
									vectorButton.at(0).setPosition(sf::Vector2f(vectorButton.at(0).getPosition().x - 50, vectorButton.at(0).getPosition().y));
									vectorButton.at(1).setPosition(sf::Vector2f(vectorButton.at(1).getPosition().x - 50, vectorButton.at(1).getPosition().y));
								}
							}
							else if (i == 1) {
								if (camera->getCenter().x != totalX - (cameraX / 2)) {
									camera->setCenter(sf::Vector2f(float(camera->getCenter().x + 50), float(camera->getCenter().y)));
									vectorButtonText.at(0).setPosition(sf::Vector2f(vectorButtonText.at(0).getPosition().x + 50, vectorButtonText.at(0).getPosition().y));
									vectorButtonText.at(1).setPosition(sf::Vector2f(vectorButtonText.at(1).getPosition().x + 50, vectorButtonText.at(1).getPosition().y));
									vectorButton.at(0).setPosition(sf::Vector2f(vectorButton.at(0).getPosition().x + 50, vectorButton.at(0).getPosition().y));
									vectorButton.at(1).setPosition(sf::Vector2f(vectorButton.at(1).getPosition().x + 50, vectorButton.at(1).getPosition().y));
								}
							}
							break;
						}
					}
				}
			}
			if (eventMain.type == sf::Event::MouseButtonPressed && eventMain.mouseButton.button == sf::Mouse::Right) {
				bool mouseOnSprite;
				for (int j = 0; j < vectorSprite.size(); j++) {
					mouseOnSprite = isMouseOnSprite(window, &vectorSprite.at(j));
					if (mouseOnSprite == true) {

						sf::RenderWindow *windowEdit = new sf::RenderWindow(sf::VideoMode(320, 250), "Edit Texture/Sprite");

						sf::String xInput;
						sf::Text xText;
						xText.setFont(font);
						xText.setFillColor(sf::Color::Black);
						xText.setCharacterSize(25);
						xText.setPosition(sf::Vector2f(110, 20));
						xText.setString(std::to_string(int(vectorSprite.at(j).getTextureRect().width * vectorSprite.at(j).getScale().x)));

						sf::String yInput;
						sf::Text yText;
						yText.setFont(font);
						yText.setFillColor(sf::Color::Black);
						yText.setCharacterSize(25);
						yText.setPosition(sf::Vector2f(110, 80));
						yText.setString(std::to_string(int(vectorSprite.at(j).getTextureRect().height * vectorSprite.at(j).getScale().y)));

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

						sf::Text rotText;
						rotText.setFont(font);
						rotText.setFillColor(sf::Color::Black);
						rotText.setCharacterSize(25);
						rotText.setString("Rotation :");
						rotText.setPosition(sf::Vector2f(20, 140));

						int rotValueCont = int(vectorSprite.at(j).getRotation());
						sf::Text rotValue;
						rotValue.setFont(font);
						rotValue.setFillColor(sf::Color::Black);
						rotValue.setCharacterSize(25);
						rotValue.setString(std::to_string(rotValueCont));
						rotValue.setPosition(sf::Vector2f(115, 140));

						sf::RectangleShape textFieldX(sf::Vector2f(200, 50));
						textFieldX.setPosition(200, 40);
						textFieldX.setFillColor(sf::Color::White);
						textFieldX.setOrigin(sf::Vector2f(100, 25));

						sf::RectangleShape textFieldY(sf::Vector2f(200, 50));
						textFieldY.setPosition(200, 100);
						textFieldY.setFillColor(sf::Color::White);
						textFieldY.setOrigin(sf::Vector2f(100, 25));

						sf::Text enterB;
						enterB.setFont(font);
						enterB.setFillColor(sf::Color::Black);
						enterB.setCharacterSize(25);
						enterB.setString("Enter");
						enterB.setPosition(sf::Vector2f(225, 170));

						sf::RectangleShape enterButton(sf::Vector2f(100.f, 80.f));
						enterButton.setPosition(250, 170);
						enterButton.setFillColor(sf::Color::White);
						enterButton.setOrigin(50, 25);

						sf::Text turnText;
						turnText.setFont(font);
						turnText.setFillColor(sf::Color::Black);
						turnText.setCharacterSize(25);
						turnText.setString("Turn");
						turnText.setPosition(sf::Vector2f(60, 190));

						sf::RectangleShape turnButton(sf::Vector2f(120.f, 40.f));
						turnButton.setPosition(70, 210);
						turnButton.setFillColor(sf::Color::White);
						turnButton.setOrigin(50, 25);

						std::vector<sf::RectangleShape> textFieldVector;
						textFieldVector.push_back(textFieldX);
						textFieldVector.push_back(textFieldY);
						textFieldVector.push_back(enterButton);
						textFieldVector.push_back(turnButton);

						auto drawButText = [&]() {
							windowEdit->draw(sizeX);
							windowEdit->draw(sizeY);
							windowEdit->draw(rotText);
							windowEdit->draw(rotValue);
							windowEdit->draw(textFieldX);
							windowEdit->draw(textFieldY);
							windowEdit->draw(enterButton);
							windowEdit->draw(enterB);
							windowEdit->draw(turnButton);
							windowEdit->draw(turnText);
							windowEdit->draw(xText);
							windowEdit->draw(yText);
						};

						enum altTop { top, alt };
						altTop direc = top;

						while (windowEdit->isOpen()) {
							sf::Event eventEdit;
							while (windowEdit->pollEvent(eventEdit)) {
								if (eventEdit.type == sf::Event::Closed) {
									xInput.clear();
									xText.setString(xInput);
									yInput.clear();
									yText.setString(yInput);
									windowEdit->close();
								}
								if (eventEdit.type == sf::Event::MouseButtonPressed && eventEdit.mouseButton.button == sf::Mouse::Left) {
									bool clickEvent;
									for (int i = 0; i < textFieldVector.size(); i++) {
										clickEvent = isMouseCliked(windowEdit, &textFieldVector.at(i));
										if (clickEvent == true) {
											if (i == 0)
												direc = top;
											else if (i == 1)
												direc = alt;
											else if (i == 3) {
												if (rotValueCont >= 355) {
													rotValueCont = 0;
												}
												else {
													rotValueCont += 5;
												}
												rotValue.setString(std::to_string(rotValueCont));
											}
											else {
												vectorSprite.at(j).setScale(
													std::atoi(xText.getString().toAnsiString().c_str()) / activeSprite->getLocalBounds().width,
													std::atoi(yText.getString().toAnsiString().c_str()) / activeSprite->getLocalBounds().height);
												vectorSprite.at(j).setRotation(rotValueCont);
												windowEdit->close();
											}
											break;
										}
									}
								}
								if (eventEdit.type == sf::Event::TextEntered && eventEdit.text.unicode < 128)
								{
									if (eventEdit.text.unicode == 8) {
										if (direc == top && xInput.getSize() != 0) {
											xInput.erase(xInput.getSize() - 1, 1);
										}
										else if (direc == alt && yInput.getSize() != 0) {
											yInput.erase(yInput.getSize() - 1, 1);
										}
									}
									else {
										if (direc == top) {
											xInput += eventEdit.text.unicode;
										}
										else if (direc == alt) {
											yInput += eventEdit.text.unicode;
										}
									}
									xText.setString(xInput);
									yText.setString(yInput);
								}
							}

							windowEdit->clear(sf::Color(169, 169, 169));
							drawButText();
							windowEdit->display();
						}

						break;
					}
				}
			}
			if (eventMain.type == sf::Event::KeyPressed && eventMain.key.code == sf::Keyboard::LControl) {
				if (LControl == true)
					LControl = false;
				else
					LControl = true;
			}
			if (eventMain.type == sf::Event::KeyPressed && eventMain.key.code == sf::Keyboard::S) {
				if (LControl == true) {
					printLevel();
					LControl = false;
				}
			}
			if (eventMain.type == sf::Event::MouseButtonReleased && eventMain.mouseButton.button == sf::Mouse::Left) {
				spriteMove = false;
			}
			if (eventMain.type == sf::Event::KeyPressed && eventMain.key.code == sf::Keyboard::J) {

				sf::RenderWindow *windowSprite = new sf::RenderWindow(sf::VideoMode(700, 160), "Create Texture/Sprite");

				sf::String playerInput;
				sf::Text playerText;
				sf::Text fileDir;
				sf::Text enterB;
				sf::RectangleShape textField(sf::Vector2f(500, 50));
				sf::RectangleShape enterButton(sf::Vector2f(100.f, 50.f));

				auto setButtonText = [&]() {
					playerText.setFont(font);
					playerText.setFillColor(sf::Color::Black);
					playerText.setCharacterSize(25);
					playerText.setPosition(sf::Vector2f(180, 20));
					///////////////////////////////////////////////
					fileDir.setFont(font);
					fileDir.setFillColor(sf::Color::Black);
					fileDir.setCharacterSize(25);
					fileDir.setString("File Directory");
					fileDir.setPosition(sf::Vector2f(20, 20));
					///////////////////////////////////////////////
					enterB.setFont(font);
					enterB.setFillColor(sf::Color::Black);
					enterB.setCharacterSize(25);
					enterB.setString("Enter");
					enterB.setPosition(sf::Vector2f(595, 100));
					//////////////////////////////////////////////
					textField.setPosition(420, 40);
					textField.setFillColor(sf::Color::White);
					textField.setOrigin(sf::Vector2f(250, 25));
					//////////////////////////////////////////////
					enterButton.setPosition(620, 115);
					enterButton.setFillColor(sf::Color::White);
					enterButton.setOrigin(50, 25);
					/////////////////////////////////////////////
				};

				setButtonText();

				while (windowSprite->isOpen()) {
					sf::Event olaylar;
					while (windowSprite->pollEvent(olaylar)) {
						if (olaylar.type == sf::Event::Closed) {
							playerInput.clear();
							playerText.setString(playerInput);
							windowSprite->close();
						}
						if (olaylar.type == sf::Event::TextEntered && olaylar.text.unicode < 128)
						{
							if (olaylar.text.unicode == 8) {
								if (playerInput.getSize() != 0) {
									playerInput.erase(playerInput.getSize() - 1, 1);
								}
							}
							else if (olaylar.text.unicode == 13) {
								std::string dosya;
								dosya = playerText.getString().toAnsiString().c_str();
								vectorFileName.push_back(dosya);

								activeText = new sf::Texture;
								if (!activeText->loadFromFile(dosya)) {
									activeText->loadFromFile("noimage.png");
								}
								activeSprite = new sf::Sprite;
								activeSprite->setTexture(*activeText);
								activeSprite->setOrigin(sf::Vector2f(activeSprite->getTextureRect().width / 2, activeSprite->getTextureRect().height / 2));
								activeSprite->setPosition(sf::Vector2f(camera->getCenter().x, 100));

								vectorTexture.push_back(*activeText);
								vectorSprite.push_back(*activeSprite);

								windowSprite->close();
								playerInput.clear();
								playerText.setString(playerInput);
								playerText.setPosition(sf::Vector2f(180, 30));
							}
							else {
								playerInput += olaylar.text.unicode;
							}
							playerText.setString(playerInput);
						}
						if (olaylar.type == sf::Event::MouseButtonPressed && olaylar.mouseButton.button == sf::Mouse::Left) {
							bool clickEvent;
							clickEvent = isMouseCliked(windowSprite, &enterButton);
							if (clickEvent == true) {
								std::string dosya;
								dosya = playerText.getString().toAnsiString().c_str();
								vectorFileName.push_back(dosya);
								std::cout << "Texture : " << dosya << std::endl;

								activeText = new sf::Texture;
								if (!activeText->loadFromFile(dosya)) {
									activeText->loadFromFile("noimage.png");
								}
								activeSprite = new sf::Sprite;
								activeSprite->setTexture(*activeText);
								activeSprite->setOrigin(sf::Vector2f(activeSprite->getTextureRect().width / 2, activeSprite->getTextureRect().height / 2));
								activeSprite->setPosition(sf::Vector2f(camera->getCenter().x, 100));

								vectorTexture.push_back(*activeText);
								vectorSprite.push_back(*activeSprite);

								windowSprite->close();
								playerInput.clear();
								playerText.setString(playerInput);
								playerText.setPosition(sf::Vector2f(180, 30));
							}
						}
					}

					windowSprite->clear(sf::Color(169, 169, 169));
					windowSprite->draw(fileDir);
					windowSprite->draw(enterButton);
					windowSprite->draw(enterB);
					windowSprite->draw(textField);
					windowSprite->draw(playerText);
					windowSprite->display();
				}

			}
			if (eventMain.type == sf::Event::KeyPressed && eventMain.key.code == sf::Keyboard::Delete) {
				for (int i = 0; i < vectorSprite.size(); i++) {
					bool mouseOnSprite = isMouseOnSprite(window, &vectorSprite.at(i));
					if (mouseOnSprite == true) {
						vectorFileName.erase(vectorFileName.begin() + i);
						vectorTexture.erase(vectorTexture.begin() + i);
						vectorSprite.erase(vectorSprite.begin() + i);
					}
				}
			}
			if (sf::Event::MouseMoved) {
				if (spriteMove == true) {
					float mouseX = sf::Mouse::getPosition(*window).x;
					float mouseY = sf::Mouse::getPosition(*window).y;

					sf::Vector2f mouseXY = window->mapPixelToCoords(sf::Vector2i(mouseX, mouseY));

					vectorSprite.at(k).setPosition(sf::Vector2f(mouseXY.x, mouseXY.y));
					scroolToGrid(&vectorSprite.at(k));
				}
			}
		}

		window->clear(sf::Color::White);
		window->setView(*camera);
		drawGrid();
		drawSprite(window);
		if (LControl == false) {
			drawButton();
		}
		window->display();
	}
}

void designer::drawSprite(sf::RenderWindow * window)
{
	for (int i = 0; i < vectorSprite.size(); i++) {
		window->draw(vectorSprite.at(i));
	}
}

bool designer::isMouseOnSprite(sf::RenderWindow * window, sf::Sprite * groundS)
{
	float mouseX = sf::Mouse::getPosition(*window).x;
	float mouseY = sf::Mouse::getPosition(*window).y;

	sf::Vector2f mouseXY = window->mapPixelToCoords(sf::Vector2i(mouseX, mouseY));

	float difX = mouseXY.x - groundS->getPosition().x;
	float difY = mouseXY.y - groundS->getPosition().y;

	float scaleX = groundS->getScale().x;
	float scaleY = groundS->getScale().y;

	if (difX < ((groundS->getTextureRect().width * scaleX) / 2) && difX > -((groundS->getTextureRect().width * scaleX) / 2)
		&& difY < ((groundS->getTextureRect().height * scaleY) / 2) && difY > -((groundS->getTextureRect().height * scaleY) / 2)) {
		return true;
	}

	return false;
}

void designer::scroolToGrid(sf::Sprite * ground)
{
	float spriteX = ground->getPosition().x;
	float spriteY = ground->getPosition().y;
	float difX, difY;

	for (difX = spriteX; difX > 25; difX -= 25) {};
	for (difY = spriteY; difY > 25; difY -= 25) {};

	if (difX > 12.5 && difY > 12.5) {
		difX = 25 - difX;
		difY = 25 - difY;
		ground->setPosition(sf::Vector2f(ground->getPosition().x + difX, ground->getPosition().y + difY));
	}
	else if (difX > 12.5 && difY < 12.5) {
		difX = 25 - difX;
		ground->setPosition(sf::Vector2f(ground->getPosition().x + difX, ground->getPosition().y - difY));
	}
	else if (difX < 12.5 && difY < 12.5) {
		ground->setPosition(sf::Vector2f(ground->getPosition().x - difX, ground->getPosition().y - difY));
	}
	else if (difX < 12.5 && difY > 12.5) {
		difY = 25 - difY;
		ground->setPosition(sf::Vector2f(ground->getPosition().x - difX, ground->getPosition().y + difY));
	}
}

void designer::printLevel()
{
	std::ofstream file;
	file.open("level.cpp", std::ios::app);

	file << "sf::Texture texture[" << vectorTexture.size() << "];" << std::endl;
	for (int i = 0; i < vectorTexture.size(); i++) {
		file << "texture[" << i << "].loadFromFile(\"" << vectorFileName.at(i) << "\");" << std::endl;
	}

	file << "sf::Sprite sprite[" << vectorSprite.size() << "];" << std::endl;
	for (int i = 0; i < vectorTexture.size(); i++) {
		file << "sprite[" << i << "].setTexture(texture[" << i << "]);" << std::endl;
	}

	for (int i = 0; i < vectorSprite.size(); i++) {
		file << "sprite[" << i << "].setScale(sf::Vector2f(" << vectorSprite.at(i).getScale().x << "," <<
			vectorSprite.at(i).getScale().y << ");" << std::endl;
	}

	for (int i = 0; i < vectorSprite.size(); i++) {
		file << "sprite[" << i << "].setRotation(" << int(vectorSprite.at(i).getRotation()) << ");" << std::endl;
	}

	for (int i = 0; i < vectorSprite.size(); i++) {
		file << "sprite[" << i << "].setOrigin(sf::Vector2f(sprite[" << i << "].getTextureRect().width * sprite[" << i << "].getScale() / 2"
			<< "," << "sprite[" << i << "].getTextureRect().height * sprite[" << i << "].getScale() / 2));" << std::endl;
	}

	for (int i = 0; i < vectorSprite.size(); i++) {
		file << "sprite[" << i << "].setPosition(sf::Vector2f(" << vectorSprite.at(i).getPosition().x << "," <<
			vectorSprite.at(i).getPosition().y << "));" << std::endl;
	}

	for (int i = 0; i < vectorSprite.size(); i++) {
		file << "window.draw(sprite[" << i << "]);" << std::endl;
	}

	file.close();
	std::cout << "Print Correct!" << std::endl;
}

bool designer::isMouseCliked(sf::RenderWindow * window, sf::RectangleShape * button)
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

