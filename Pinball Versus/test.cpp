#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameLoop.h"
#include "Menu.h"
#include <fstream>


const float resize = 0.8073;
float easing = 0.08f;
float rotation = 25.0;
float finalRotation = 25.0f;
int pinNO = 16, bumpNO = 6;
void selectMode(sf::RenderWindow& window);
void viewInstructions(sf::RenderWindow& window);

int main() {
	
	
//	std::cout<<s<<std::endl;

	sf::RenderWindow window(sf::VideoMode(1024, 700), "Pinball Versus");
	std::string menu1Strings[] = { "Play", "Instructions","Exit" };
	Menu menu1(window.getSize().x, window.getSize().y, menu1Strings, 3);
	sf::Texture background;
	background.loadFromFile("Images/background.png");
	sf::RectangleShape backgroundRect;
	backgroundRect.setSize(sf::Vector2f(1024, 700));
	backgroundRect.setTexture(&background);
	
	while (window.isOpen())
	{
		sf::Event event;
		window.draw(backgroundRect);
		menu1.draw(window);


		while (window.pollEvent(event))

		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu1.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu1.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu1.GetPressedItem())
					{
					case 0:
						window.clear();
						selectMode(window);
						break;
					case 1:
						viewInstructions(window);

						break;
					case 2:
						window.close();
						break;

					}
				}

			}
		}
		window.display();
	}
	//game.run(window, b, ball, bumpers, pins,arrow);


	return 0;
}

void selectMode(sf::RenderWindow& window) {
	std::string menu1Strings[] = { "SCORE 5 TO WIN", "2 MINUTES TIMED BATTLE"};
	Menu menu1(window.getSize().x, window.getSize().y, menu1Strings, 2);
	sf::Texture background;
	background.loadFromFile("Images/background.png");
	sf::RectangleShape backgroundRect;
	backgroundRect.setSize(sf::Vector2f(1024, 700));
	backgroundRect.setTexture(&background);
	GameLoop game;
	while (window.isOpen())
	{
		sf::Event event;
		window.draw(backgroundRect);
		menu1.draw(window);


		while (window.pollEvent(event))

		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu1.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu1.MoveDown();
					break;
				case sf::Keyboard::Escape:
					return;
					break;

				case sf::Keyboard::Return:
					switch (menu1.GetPressedItem())
					{
					case 0:
						window.clear();
						game.run(window, 0);
						return;
						break;
					case 1:
						window.clear();
						game.run(window, 1);
						break;
						return;

					}
				}

			}
		}
		window.display();
	}

	
}

void viewInstructions(sf::RenderWindow& window) {
	std::ifstream inFile;
	inFile.open("instructions.txt");//open the input file
	window.clear();
	std::string s;
	std::getline(inFile, s, (char)inFile.eof());
	sf::Text text;
	sf::Font font;
	font.loadFromFile("Fonts/ubuntu.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Yellow);
	text.setString(s);
	text.setPosition(sf::Vector2f(100, 100));
	sf::Texture background;
	background.loadFromFile("Images/background.png");
	sf::RectangleShape backgroundRect;
	backgroundRect.setSize(sf::Vector2f(1024, 700));
	backgroundRect.setTexture(&background);
	
	while (window.isOpen())
	{
		sf::Event event;
		window.draw(backgroundRect);
		window.draw(text);
		while (window.pollEvent(event))

		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					return;
					break;

					
				}

			}
		}
		window.display();
	}

}

