#pragma once
#include<SFML\Graphics.hpp>
class Ball
{
public:
	const float GRAVITY = 300.0f;
	float radius;
	sf::CircleShape shape;
	sf::Vector2f globalPosition;
	float angleInDegrees, angleInRadians, xVelocity, yVelocity, magVelocity;

public:
	Ball(float radius);
	~Ball();
	void draw(sf::Time dt);
	void render(sf::RenderWindow* window );
	void setParams(float angleInDegrees, float magVelocity);
	void setParams2(float xVelocity, float yVelocity);
};

