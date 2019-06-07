#pragma once
#include"BumperObstacle.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include "Vector.h"
class Board
{
public:
	sf::RectangleShape arena;
	std::vector<BoardObject> itemList;
	sf::Texture board;
	float offset_x;
	const float resize = 0.8073;
public:
	Board(sf::RenderWindow& window, float width, float height);
	~Board();
	void addItem(BumperObstacle& obj);
	void addItem(BoardObject* obj);

	void draw(sf::RenderWindow& window, Ball& ball);
	void render(sf::RenderWindow* window);
};

