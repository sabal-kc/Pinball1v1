#pragma once
#include<SFML/Graphics.hpp>
#include "Ball.h"
#include "Flipper.h"
sf::Vector2f newVector(float ix, float iy, float fx, float fy);
float dotproduct(sf::Vector2f source, sf::Vector2f dest);

void drawline(sf::RenderWindow &window, sf::Vector2f ip, sf::Vector2f fp, sf::Color color);
sf::Vector2f projpt(sf::Vector2f v1, sf::Vector2f v2);
sf::Vector2f trans(sf::Vector2f vecTotrans, sf::Vector2f transpt);

float dist_ptl(sf::Vector2f v1, sf::Vector2f v2, Ball& b);
bool isCollided(float d, Ball& b);
bool checkCollision(Ball &ball, Flipper &flipper, bool &collided, bool &hit, bool &rolling, sf::RenderWindow &window);