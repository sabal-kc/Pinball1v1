#include "Ball.h"
#include<SFML\Graphics.hpp>





Ball::Ball(float radius){
	this->radius = radius;
	shape.setRadius(radius);
	shape.setPosition(0, 486);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setFillColor(sf::Color::White);
}

Ball::~Ball(){
}

void Ball::draw(sf::Time dt){
	sf::Vector2f position = shape.getPosition();
	globalPosition.x = position.x-radius;
	globalPosition.y = position.y-radius;

	//Collison with boundaries
	if (position.y <= shape.getRadius()){
		yVelocity *= -1;
		shape.setPosition(position.x, shape.getRadius());
	}
	if (shape.getRadius() + position.y >= 512){
		yVelocity *= -1;
		shape.setPosition(position.x, 512 - shape.getRadius());
	}
	if (position.x <= shape.getRadius()){
		xVelocity *= -1;
		shape.setPosition(shape.getRadius(), position.y);
	}
	if (shape.getRadius() + position.x >= 1024){
		xVelocity *= -1;
		shape.setPosition(1024 - shape.getRadius(), position.y);
	}
	if (shape.getRadius() + position.y >= 512){
		yVelocity = yVelocity / 2.0f;
	}
	yVelocity += GRAVITY * dt.asSeconds();
	shape.move(xVelocity * dt.asSeconds(), yVelocity * dt.asSeconds());

}

void Ball::render(sf::RenderWindow* window){
	window->draw(shape);
}

//Call setParams when there is change in mag or direction
void Ball::setParams(float angleInDegrees, float magVelocity){
	this->angleInDegrees = angleInDegrees;
	this->magVelocity = magVelocity;
	angleInRadians = angleInDegrees * 2 * 3.1415 / 360;
	xVelocity = cos(angleInRadians)*magVelocity;
	yVelocity = sin(angleInRadians)*magVelocity;
}

void Ball::setParams2(float xVelocity, float yVelocity)
{
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
}


