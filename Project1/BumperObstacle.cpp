#include "BumperObstacle.h"

#include "GeneralUtils.h"




BumperObstacle::BumperObstacle(sf::Vector2f position, sf::Color color)
{
	center = position;
	shape.setRadius(RADIUS);
	shape.setPosition(position);
	shape.setFillColor(color);
}


BumperObstacle::~BumperObstacle()
{
}

void BumperObstacle::render(sf::RenderWindow * window)
{
	window->draw(shape);
}

bool BumperObstacle::collison(Ball ball)
{
	if (GeneralUtils::dist(center, ball.globalPosition) <= RADIUS+ball.radius)
		return true;
	return false;
}

