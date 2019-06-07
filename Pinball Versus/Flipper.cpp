#pragma once
#include "Flipper.h"
Flipper::Flipper()
{
}
Flipper::Flipper(sf::Vector2f pos, sf::Vector2f size, float angle, sf::Vector2f origin, sf::Vector2f scale)
{
	flipper.setSize(size);
	flipper.setPosition(pos);
	flipper.setRotation(angle);
	flipper.setScale(scale);
	flipper.setOrigin(origin);


	flip.loadFromFile("Images/flip.png");
	sprite.setSize(sf::Vector2f(100, 50));
	sprite.setTexture(&flip);
	sprite.setPosition(flipper.getPosition().x, flipper.getPosition().y - 12.0f);
	sprite.setRotation(flipper.getRotation());
	sprite.setScale(flipper.getScale());
	sprite.setOrigin(origin);

}

void Flipper::render(sf::RenderWindow &window)
{
	window.draw(sprite);
}


Flipper::~Flipper()
{
}
