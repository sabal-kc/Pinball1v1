#pragma once
#include<SFML\Graphics.hpp>
#include "Ball.h"
#include "BoardObject.h"
class BumperObstacle : public BoardObject
{
public:
	int RADIUS = 30;
	sf::CircleShape shape;
	sf::Vector2f center;
	sf::Sprite light;
	sf::Sprite lightmap;
	float mass1 = 1, mass2 = 50;

public:
	BumperObstacle();
	BumperObstacle(sf::Vector2f position, sf::Color color);
	~BumperObstacle();
	void draw();
	void render(sf::RenderWindow* window);
	bool collision(Ball* ball);
	void lightEffectsDraw();
	void lightEffectsRender(sf::RenderWindow* window);
	void setPosColor(sf::Vector2f position, sf::Color color);

};

