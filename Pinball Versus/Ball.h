#pragma once
#include<SFML\Graphics.hpp>
#include "BoardObject.h"

class Ball
{
public:
	float GRAVITY = 200.0f;
	float radius;
	sf::CircleShape shape;
	sf::Vector2f globalPosition;
	sf::Vector2f velocity, acceleration;
	float angleInDegrees, angleInRadians, xVelocity, yVelocity, magVelocity;
	sf::Vector2f intialPos1 = sf::Vector2f(300, 300);
	sf::Vector2f intialPos2 = sf::Vector2f(300, 450);


	float initXvel = 0, intitYvel = 10;

public:
	Ball(float radius);
	Ball();
	~Ball();
	void draw(sf::Time dt);
	void render(sf::RenderWindow* window );
	void setParams(float angleInDegrees, float magVelocity);
	void setParams2(float xVelocity, float yVelocity);
	void changePosition(sf::Vector2f newPos);
	void applyForce() {
		this->acceleration.y = 0.0f;
	}

	void release() {
		this->acceleration.y = 0.001f;
	}
	void setVelocity(sf::Vector2f vel) {
		velocity = vel;
		this->setParams2(vel.x, vel.y);
	}
	void reset(sf::RenderWindow & window, int playerNo);
};

