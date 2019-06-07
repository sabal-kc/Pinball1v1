#include<SFML/Graphics.hpp>
#include<iostream>
#include "Ball.h"
#include "Flipper.h"
sf::Vector2f newVector(float ix, float iy, float fx, float fy)
{
	float nx, ny, dx, dy;
	nx = fx - ix;
	ny = fy - iy;

	return sf::Vector2f(nx, ny);
}
sf::Vector2f trans(sf::Vector2f vecTotrans, sf::Vector2f transpt)
{
	sf::Vector2f transformedpt;
	transformedpt.x = vecTotrans.x + transpt.x;
	transformedpt.y = vecTotrans.y + transpt.y;
	return transformedpt;
}

float dotproduct(sf::Vector2f source, sf::Vector2f dest)
{
	return (source.x * dest.x + source.y * dest.y);
}

void drawline(sf::RenderWindow &window, sf::Vector2f ip, sf::Vector2f fp, sf::Color color)
{
	sf::Vertex line[] = {
		sf::Vertex(ip),
		sf::Vertex(fp)
	};
	line[0].color = color;
	line[1].color = color;
	window.draw(line, 2, sf::Lines);
}

sf::Vector2f projpt(sf::Vector2f v1, sf::Vector2f v2)
{

	float rx, ry;
	sf::Vector2f closestpt;
	float fdl = dotproduct(v1, v2);
	float ldl = dotproduct(v2, v2);
	float mul = fdl / ldl;
	rx = v2.x * mul;
	ry = v2.y * mul;
	return sf::Vector2f(rx, ry);
}

float dist_ptl(sf::Vector2f v1, sf::Vector2f v2, Ball& b) {
	float m = (v2.y - v1.y) / (v2.x - v1.x);
	float numerator = m * (b.globalPosition.x) - (b.globalPosition.y) - (m*v1.x) + v1.y;
	float denominator = sqrt(m*m + 1);
	float dist = abs(numerator / denominator);

	return dist;
}

bool isCollided(float d, Ball& b) {
	bool collided = false;

	if (d <= b.radius)
	{
		collided = true;
	}
	return collided;
}

bool checkCollision(Ball &ball, Flipper &flipper, bool &collided, bool &hit, bool &rolling, sf::RenderWindow &window)
{
	sf::Vector2f flippos(flipper.flipper.getPosition());
	float flipperlength;
	float angle = flipper.flipper.getRotation() * 3.1415f / 180.0f;
	flipperlength = flipper.flipper.getSize().x;
	sf::Vector2f vertex1, vertex2;
	sf::Vector2f vertex[2];

	if (flipper.flipper.getPosition().y >= window.getSize().x / 2) {
		if (flipper.flipper.getScale().x == -1.0f)
			vertex2 = sf::Vector2f(flippos.x - flipperlength * cos(angle), flippos.y - flipperlength * sin(angle));
		else
			vertex2 = sf::Vector2f(flippos.x + flipperlength * cos(angle), flippos.y + flipperlength * sin(angle));
		vertex[0] = sf::Vector2f(flippos.x, flippos.y);
		vertex[1] = vertex2;
	}
	if (flipper.flipper.getPosition().y <= window.getSize().x / 2) {
		if (flipper.flipper.getScale().x == -1.0f)
			vertex2 = sf::Vector2f(flippos.x - flipperlength * cos(angle), flippos.y - flipperlength * sin(angle));
		else
			vertex2 = sf::Vector2f(flippos.x + flipperlength * cos(angle), flippos.y + flipperlength * sin(angle));
		vertex[0] = sf::Vector2f(flippos.x, flippos.y);
		vertex[1] = vertex2;

	}


	sf::Vector2f transpt = vertex[0];
	sf::Vector2f vecA = newVector(vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y);
	sf::Vector2f transvecA = trans(vecA, transpt);
	sf::Vector2f vecB = newVector(vertex[0].x, vertex[0].y, ball.globalPosition.x, ball.globalPosition.y);
	sf::Vector2f transvecB = trans(vecB, transpt);
	sf::Vector2f originprojpt = projpt(vecB, vecA);
	sf::Vector2f closestpt = trans(originprojpt, transpt);
	sf::Vector2f reactd = newVector(ball.globalPosition.x, ball.globalPosition.y, closestpt.x, closestpt.y);

	float dx = closestpt.x - ball.globalPosition.x;
	float dy = closestpt.y - ball.globalPosition.y;
	float dx2 = closestpt.x - vertex[0].x;
	float dy2 = closestpt.y - vertex[0].y;

	float dist = sqrt(dx*dx + dy * dy);

	float plength = sqrt(dx2*dx2 + dy2 * dy2);
	collided = isCollided(dist, ball);
	if (collided)
	{
		if (plength <= flipperlength) {
			float dp = dotproduct(originprojpt, vecA);
			if (dp >= 0) {
				//std::cout << "Collision" << std::endl;

				if (hit)
				{
					if (flipper.flipper.getPosition().y >= window.getSize().x / 2) {
						ball.xVelocity = -reactd.x * plength;
						ball.yVelocity = -reactd.y * plength;
					}
					if (flipper.flipper.getPosition().y <= window.getSize().x / 2) {
						ball.xVelocity = +reactd.x * plength;
						ball.yVelocity = +reactd.y * plength;
					}
				}
				else
				{
					if (flipper.flipper.getScale().x == -1.0f)
						ball.setParams(flipper.flipper.getRotation(), -100);
					else
						ball.setParams(flipper.flipper.getRotation(), 100);
					rolling = true;
				}
				if (hit&&rolling)
				{

					ball.xVelocity = -reactd.x * plength * 2;
					ball.yVelocity = -reactd.y * plength * 2;

				}
			}
		}


	}
	else
	{
		collided = false;

	}
	return collided;
}