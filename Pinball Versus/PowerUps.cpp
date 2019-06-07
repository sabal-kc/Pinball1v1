#include "PowerUps.h"



PowerUps::PowerUps()
{
	normal.loadFromFile("Images/GameBall.png");
}


PowerUps::~PowerUps()
{
}

void PowerUps::changeRadius(Ball & ball, float newRadius)
{
	if (newRadius > 10) {
		ball.radius = newRadius;
		ball.shape.setRadius(newRadius);
	}
	ball.GRAVITY = ball.radius * 200 /10;
}

void PowerUps::changeTransparency(Ball & ball, float trans)
{
	ball.shape.setFillColor(sf::Color(255, 255, 255, trans));
}

void PowerUps::resetBall(Ball & ball)
{
	ball.radius = 10;
	ball.GRAVITY *= -1;
	ball.shape.setRadius(10);
	ball.shape.setTexture(&normal);
	ball.shape.setFillColor(sf::Color(255, 255, 255, 255));
}
