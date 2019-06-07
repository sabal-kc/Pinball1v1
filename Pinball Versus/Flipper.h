#pragma once
#include<SFML\Graphics.hpp>

class Flipper
{
public:
	sf::RectangleShape flipper;
	sf::RectangleShape sprite;
	sf::Texture flip;

	float rotation;
	Flipper();
	Flipper(sf::Vector2f pos, sf::Vector2f size, float angle, sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f), sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
	//void designFlipper();
	~Flipper();
	void render(sf::RenderWindow &window);
};

