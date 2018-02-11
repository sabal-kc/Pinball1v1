//#include <SFML\Graphics.hpp>
//#include<iostream>
//int main() {
//	sf::Vector2f screenSize(700.0f,700.0f);
//	sf::Vector2f initialPos(screenSize.x / 2, screenSize.y / 2);
//	float ballSize = 5.0f;
//	float surfaceFriction = 0.99f;
//	const sf::Vector2f gravity(0.f, 0.1f);
//	sf::Vector2f velocity(1.0f, 1.0f);
//	velocity += gravity;
//	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Pinball");
//	sf::CircleShape ball(ballSize);
//	ball.setFillColor(sf::Color::Blue);
//	ball.setPosition(initialPos);
//
//	//Game loop
//	while (window.isOpen()) {
//
//		
//		//Event handling
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			switch (event.type) {
//			case sf::Event::Closed:
//				window.close();
//				break;
//			}
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//			velocity.x += 0.2f;
//			velocity.y += 0.2f;
//		}
//		if (ball.getPosition().x < 0)
//			velocity.x=abs(velocity.x)*surfaceFriction;
//		if (ball.getPosition().x >= screenSize.x)
//			velocity.x = -(velocity.x)*surfaceFriction;
//		if (ball.getPosition().y < 0)
//			velocity.y = abs(velocity.y)*surfaceFriction;
//		if (ball.getPosition().y >= screenSize.y)
//			velocity.y = -(velocity.y)*surfaceFriction;
//		ball.move(velocity);
//		
//		//Update items
//		window.clear();
//		window.draw(ball);
//		window.display();
//	}
//
//	return 0;
//}