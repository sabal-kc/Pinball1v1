#include "Board.h"
#include <iostream>

Board::Board(sf::RenderWindow& window, float width, float height)
{
	//Arena
	arena.setSize(sf::Vector2f(width, height));
	offset_x = (window.getSize().x - arena.getSize().x) / 2;
	arena.setPosition(sf::Vector2f(offset_x, 0));
	if (board.loadFromFile("Images/board.png"))
		std::cout << "Success";
	arena.setTexture(&board);

}


Board::~Board()
{
}

void Board::addItem(BoardObject* obj)
{
	//std::cout << "Added" << std::endl;
	//this->itemList.push_back(*obj);
}

void Board::draw(sf::RenderWindow& window, Ball& ball)
{
	//Arena	
	//TL-ML & ML1-ML2
	float dist1 = dist_ptl(sf::Vector2f(offset_x + resize * 260, 135 * resize), sf::Vector2f(offset_x + resize * 108, 207 * resize), ball);
	float dist2 = dist_ptl(sf::Vector2f(offset_x + resize * 108, 207 * resize), sf::Vector2f(offset_x + resize * 110, 665 * resize), ball);

	if (isCollided(dist1, ball)) {
		if (ball.globalPosition.x > offset_x + resize * 108 && ball.globalPosition.x < 260 * resize + offset_x)
		{

			ball.shape.setPosition(ball.globalPosition.x + ball.radius / 8, ball.globalPosition.y);
			ball.xVelocity *= -0.9;

		}

		//ROLLING
		//std::cout << "Collide on Tl to ML" << std::endl;
	}
	if (isCollided(dist2, ball))
	{
		ball.xVelocity *= 0.9;
		ball.shape.setPosition(ball.globalPosition.x + ball.radius / 32, ball.globalPosition.y);

	}

	//  ML2-BL  MR2-BR
	float dist3 = dist_ptl(sf::Vector2f(offset_x + resize * 110, 665 * resize), sf::Vector2f(offset_x + resize * 260, 731 * resize), ball);
	float dist4 = dist_ptl(sf::Vector2f(offset_x + resize * 660, 665 * resize), sf::Vector2f(offset_x + resize * 507, 733 * resize), ball);

	if (isCollided(dist3, ball)) {
		if (ball.globalPosition.x > offset_x + resize * 110 && ball.globalPosition.x < 260 * resize + offset_x)
		{
			ball.shape.setPosition(ball.globalPosition.x + ball.radius / 8, ball.globalPosition.y);
			ball.xVelocity *= -0.9;
		}

	}
	if (isCollided(dist4, ball))
	{
		if (ball.globalPosition.x > offset_x + resize * 507 && ball.globalPosition.x < 660 * resize + offset_x)
		{
			ball.xVelocity *= -0.9;
			ball.shape.setPosition(ball.globalPosition.x - ball.radius / 8, ball.globalPosition.y);
		}
	}

	float distx = dist_ptl(sf::Vector2f(offset_x + resize * 260, 135 * resize), sf::Vector2f(offset_x + resize * 260, 731 * resize), ball);
	float disty = dist_ptl(sf::Vector2f(offset_x + resize * 660, 665 * resize), sf::Vector2f(offset_x + resize * 507, 733 * resize), ball);

	//TR-MR1 & MR1-MR2
	float dist5 = dist_ptl(sf::Vector2f(offset_x + resize * 501, 133 * resize), sf::Vector2f(offset_x + resize * 658, 198 * resize), ball);
	float dist6 = dist_ptl(sf::Vector2f(offset_x + resize * 658, 198 * resize), sf::Vector2f(offset_x + resize * 660, 665 * resize), ball);
	if (isCollided(dist5, ball)) {
		if (ball.globalPosition.x > offset_x + resize * 501 && ball.globalPosition.x < 658 * resize + offset_x)
		{
			ball.xVelocity *= -0.9;
			ball.shape.setPosition(ball.globalPosition.x - ball.radius / 8, ball.globalPosition.y);
		}
	}
	if (isCollided(dist6, ball)) {
		ball.xVelocity *= -0.5;
		ball.shape.setPosition(ball.globalPosition.x - ball.radius / 32, ball.globalPosition.y - ball.radius / 32);
	}

	//TL-TR & BL-BR
	float dist7 = dist_ptl(sf::Vector2f(offset_x + resize * 262, 30 * resize), sf::Vector2f(offset_x + resize * 502, 30 * resize), ball);
	float dist8 = dist_ptl(sf::Vector2f(offset_x + resize * 262, 838 * resize), sf::Vector2f(offset_x + resize * 502, 832 * resize), ball);
	/*if (isCollided(dist7, ball)) {
		ball.yVelocity *= +0.5;
		ball.shape.setPosition(ball.globalPosition.x, ball.globalPosition.y + ball.radius / 32);

	}
	if (isCollided(dist8, ball)) {
		ball.yVelocity *= -0.5;
		ball.shape.setPosition(ball.globalPosition.x, ball.globalPosition.y - ball.radius / 32);
	}*/


	//item.collision(&ball);
	/*itemList[0].draw();
	std::cout << typeid(itemList[0]).name() << std::endl;*/
}

void Board::render(sf::RenderWindow* window)
{
	window->draw(arena);

	//Tl-ML No collide Region
	drawline(*window, sf::Vector2f(offset_x + resize * 260, 135 * resize), sf::Vector2f(offset_x + resize * 108, 207 * resize), sf::Color::Blue);
	//TR-MR
	drawline(*window, sf::Vector2f(offset_x + resize * 501, 133 * resize), sf::Vector2f(offset_x + resize * 658, 198 * resize), sf::Color::Blue);
	//t


	//ML1-ML2
	drawline(*window, sf::Vector2f(offset_x + resize * 108, 207 * resize), sf::Vector2f(offset_x + resize * 110, 665 * resize), sf::Color::Blue);
	//ML2-BL
	drawline(*window, sf::Vector2f(offset_x + resize * 110, 665 * resize), sf::Vector2f(offset_x + resize * 260, 731 * resize), sf::Color::Blue);

	//MR1-MR2
	drawline(*window, sf::Vector2f(offset_x + resize * 658, 198 * resize), sf::Vector2f(offset_x + resize * 660, 665 * resize), sf::Color::Blue);
	//MR2-BR
	drawline(*window, sf::Vector2f(offset_x + resize * 660, 665 * resize), sf::Vector2f(offset_x + resize * 507, 733 * resize), sf::Color::Blue);

	//TL-TR
	drawline(*window, sf::Vector2f(offset_x + resize * 262, 30 * resize), sf::Vector2f(offset_x + resize * 502, 30 * resize), sf::Color::Blue);

	//BL-BR
	drawline(*window, sf::Vector2f(offset_x + resize * 262, 838 * resize), sf::Vector2f(offset_x + resize * 502, 838 * resize), sf::Color::Blue);




}
