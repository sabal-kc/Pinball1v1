#include "Menu.h"
#include<SFML\Graphics.hpp>
#define SFML_NO_DEPRECATED_WARNINGS

Menu::Menu(float width, float height, std::string s[], int size)
{
	this->size = size;
	if (!font.loadFromFile("Fonts/horizon.otf"))
	{
		// handle error
	}
	for (int i = 0;i < size;i++) {
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setString(s[i]);
		menu[i].setPosition(sf::Vector2f(width / 2-50, 200+height / (size + 1) * i+1));
	}

	menu[0].setFillColor(sf::Color::Red);
	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < this->size; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < size)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}