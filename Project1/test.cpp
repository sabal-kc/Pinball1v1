#include <iostream>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Ball.h"
#include "BumperObstacle.h"
#include "GeneralUtils.h"

float yVelocity;
int main(){
	//AssetManager manager;
	//sf::Sprite sprite1 = sf::Sprite(AssetManger::GetTexture("test.png"));

	bool toMove = false;
	sf::RectangleShape line(sf::Vector2f(2, 500));
	line.setPosition(70, 200);
	line.setOutlineThickness(2);
	line.setOutlineColor(sf::Color::White);
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Test");
	sf::Clock clock;
	float angleInDegrees = 225;
	float magVelocity = 100;
	float mass1 = 1, mass2 = 2;
	Ball ball(10);
	BumperObstacle b1(sf::Vector2f(100, 100), sf::Color::Blue);
	BumperObstacle b2(sf::Vector2f(200, 100), sf::Color::Red);
	BumperObstacle b3(sf::Vector2f(300, 100), sf::Color::Green);
	ball.setParams(angleInDegrees, magVelocity);
	while (window.isOpen()){
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
				
			if (event.type == sf::Event::KeyReleased){
				if (event.key.code == sf::Keyboard::Space)
					toMove = true;
			}

			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Num1)
					ball.setParams(225, 100);
				if (event.key.code == sf::Keyboard::Num2)
					ball.setParams(225, 300);
				if (event.key.code == sf::Keyboard::Num3)
					ball.setParams(225, 600);
				if (event.key.code == sf::Keyboard::Num4)
					ball.setParams(225, 1000);
				if (event.key.code == sf::Keyboard::Space)
					toMove = false;
			}
		}
		sf::Vector2f d = GeneralUtils::closestpointonline(ball.globalPosition.x, ball.globalPosition.y, ball.globalPosition.x + ball.xVelocity, ball.yVelocity + ball.globalPosition.y, b1.center.x, b1.center.y);
		double closestdistsq = pow(b1.center.x - d.x, 2) + pow((b1.center.y - d.y), 2);
		if (b1.collison(ball)) {
			std::cout << "YES1" << std::endl;
			ball.setParams2(-ball.xVelocity, ball.yVelocity);
		}
		/*if (closestdistsq <= pow(ball.radius + b1.RADIUS, 2)) {
			std::cout << "YES2" << std::endl;
			double backdist = sqrt(pow(ball.radius + b1.RADIUS, 2) - closestdistsq);
			double movementvectorlength = sqrt(pow(ball.xVelocity, 2) + pow(ball.yVelocity, 2));
			double c_x = d.x - backdist * (ball.xVelocity / movementvectorlength);
			double c_y = d.y - backdist * (ball.yVelocity / movementvectorlength);
			double collisiondist = sqrt(pow(b1.center.x - c_x, 2) + pow(b1.center.y - c_y, 2));
			double n_x = (b1.center.x - c_x) / collisiondist;
			double n_y = (b1.center.y - c_y) / collisiondist;
			double p = 2 * (ball.xVelocity * n_x + ball.yVelocity * n_y) /(mass1 + mass2);
			double w_x = ball.xVelocity - p * mass1 * n_x - p * mass2 * n_x;
			double w_y = ball.yVelocity - p * mass1 * n_y - p * mass2 * n_y;
			ball.setParams2(w_x, w_y);

		}*/

		window.clear();
		ball.draw(dt);
		ball.render(&window);
		b1.render(&window);
		b2.render(&window);
		b3.render(&window);
		//b1.render(&window);
		window.draw(line);
		window.display();
	}
	return 0;
}