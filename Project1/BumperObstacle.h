#pragma once
#include<SFML\Graphics.hpp>
#include "Ball.h"
class BumperObstacle
{
public:
	const int RADIUS = 30;
	sf::CircleShape shape;
	sf::Vector2f center;

public:
	BumperObstacle(sf::Vector2f position, sf::Color color);
	~BumperObstacle();
	void render(sf::RenderWindow* window);
	bool collison(Ball ball);
};

