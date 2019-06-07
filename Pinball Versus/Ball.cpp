#include "Ball.h"
#include<SFML\Graphics.hpp>





Ball::Ball(float radius){
	this->radius = radius;
	this->shape.setRadius(radius);
	this->shape.setPosition(400, 486);
	this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());
	this->shape.setFillColor(sf::Color::White);
	sf::Texture texture;
	texture.loadFromFile("Images/GameBall.png");
	this->shape.setTexture(&texture);
}

Ball::Ball()
{
}

Ball::~Ball(){
}

void Ball::draw(sf::Time dt){
	sf::Vector2f position = shape.getPosition();
	this->globalPosition.x = position.x;
	this->globalPosition.y = position.y;

	velocity += acceleration;
	position += velocity;
	this->yVelocity += this->GRAVITY * dt.asSeconds();
	this->shape.move(this->xVelocity * dt.asSeconds(), this->yVelocity * dt.asSeconds());

}

void Ball::render(sf::RenderWindow* window){
	window->draw(this->shape);
}

//Call setParams when there is change in mag or direction
void Ball::setParams(float angleInDegrees, float magVelocity){
	this->angleInDegrees = angleInDegrees;
	this->magVelocity = magVelocity;
	this->angleInRadians = angleInDegrees * 2 * 3.1415 / 360;
	this->xVelocity = cos(angleInRadians)*magVelocity;
	this->yVelocity = sin(angleInRadians)*magVelocity;
	this->velocity = sf::Vector2f(xVelocity, yVelocity);
}

void Ball::setParams2(float xVelocity, float yVelocity)
{
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
	this->velocity = sf::Vector2f(xVelocity, yVelocity);
	this->magVelocity = sqrt(xVelocity*xVelocity + yVelocity*yVelocity);
	this->angleInRadians = atan(yVelocity / xVelocity);
}

void Ball::changePosition(sf::Vector2f newPos)
{
	this->shape.move(newPos);
}
void Ball::reset(sf::RenderWindow & window, int playerNo)
{
	if (playerNo == 1)
	{
		this->shape.setPosition(intialPos1);
		this->setParams2(initXvel, intitYvel);
	}
	if (playerNo == 2)
	{
		this->shape.setPosition(intialPos2);
		this->setParams2(initXvel, intitYvel);
	}
}








