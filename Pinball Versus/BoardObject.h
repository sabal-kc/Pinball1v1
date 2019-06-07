#pragma once
#include <SFML\Graphics.hpp>
#include "Ball.h"

class BoardObject
{
public:
	BoardObject();
	~BoardObject();
	void draw();
	//virtual	bool collision(Ball* ball);
	void render(sf::RenderWindow* window);
};

