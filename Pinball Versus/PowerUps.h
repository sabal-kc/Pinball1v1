#pragma once
#include "Ball.h"
#include <SFML\Graphics.hpp>
class PowerUps
{
public:
	sf::Texture normal;
public:
	PowerUps();
	~PowerUps();
	void changeRadius(Ball& ball, float newRadius);
	void changeTransparency(Ball& ball, float trans);
	void resetBall(Ball& ball);
};

