#include "GameLoop.h"
#include"SFML\Audio.hpp"
#


GameLoop::GameLoop()
{
	

	


}


GameLoop::~GameLoop()
{
}

void GameLoop::run(sf::RenderWindow& window,int gameMode)
{
	
	//Board
	Board b(window, 768 * resize, 700);


	//Ball
	Ball ball(10);
	sf::Texture ballTexture;
	ballTexture.loadFromFile("Images/GameBall.png");
	ball.shape.setTexture(&ballTexture);
	float initXvel = 0, intitYvel = 10;
	ball.setParams2(initXvel, intitYvel);

	//Bumper
	float offset_x = (window.getSize().x - b.arena.getSize().x) / 2;
	BumperObstacle b1(sf::Vector2f(400, 400), sf::Color::Blue);
	BumperObstacle bumpers[6];
	sf::Vector2f bumperPositions[6] = { sf::Vector2f(offset_x + 205 * resize,330 * resize),sf::Vector2f(window.getSize().x - offset_x - 205 * resize,330 * resize), sf::Vector2f(offset_x + 380 * resize,360 * resize),
		sf::Vector2f(offset_x + 205 * resize,window.getSize().y - 330 * resize),sf::Vector2f(window.getSize().x - offset_x - 205 * resize,window.getSize().y - 330 * resize), sf::Vector2f(offset_x + 380 * resize,window.getSize().y - 360 * resize) };



	bool bumperIsActive[6] = { false,false, false, false, false, false };
	int bumperBlinkCount[6] = { 0, 0, 0, 0, 0, 0 };
	sf::Texture bumperTex;
	bumperTex.loadFromFile("Images/BumpB.png");
	for (int i = 0;i < bumpNO;i++) {
		bumpers[i].setPosColor(bumperPositions[i], sf::Color::White);
		bumpers[i].shape.setTexture(&bumperTex);
	}


	sf::Texture bumperActiveTex1, bumperActiveTex2;
	bumperActiveTex1.loadFromFile("Images/Bump1B.png");
	bumperActiveTex2.loadFromFile("Images/Bump1.png");
	//Pins
	const int PINS_NUMBER = 16;
	BumperObstacle pins[PINS_NUMBER];
	sf::Vector2f pinPos[PINS_NUMBER] = {
		sf::Vector2f(offset_x + 170 * resize,470 * resize),sf::Vector2f(offset_x + 255 * resize,470 * resize),
		sf::Vector2f(offset_x + 170 * resize,220 * resize),sf::Vector2f(offset_x + 255 * resize,220 * resize),

		sf::Vector2f(window.getSize().x - offset_x - 170 * resize,470 * resize),sf::Vector2f(window.getSize().x - offset_x - 255 * resize,470 * resize),
		sf::Vector2f(window.getSize().x - offset_x - 170 * resize,220 * resize),sf::Vector2f(window.getSize().x - offset_x - 255 * resize,220 * resize),

		sf::Vector2f(offset_x + 170 * resize,window.getSize().y - 470 * resize),sf::Vector2f(offset_x + 255 * resize,window.getSize().y - 470 * resize),
		sf::Vector2f(offset_x + 170 * resize,window.getSize().y - 220 * resize),sf::Vector2f(offset_x + 255 * resize,window.getSize().y - 220 * resize),

		sf::Vector2f(window.getSize().x - offset_x - 170 * resize,window.getSize().y - 470 * resize),sf::Vector2f(window.getSize().x - offset_x - 255 * resize,window.getSize().y - 470 * resize),
		sf::Vector2f(window.getSize().x - offset_x - 170 * resize,window.getSize().y - 220 * resize),sf::Vector2f(window.getSize().x - offset_x - 255 * resize,window.getSize().y - 220 * resize)

	};
	for (int i = 0;i < PINS_NUMBER;i++) {
		pins[i].RADIUS = 3.0f;
		pins[i].setPosColor(pinPos[i], sf::Color::White);

	}
	////RectangleObstacle
	//RectangleObstacle obs(sf::Vector2f(0, 0), sf::Vector2f(100, 100));


	//Arrow
	sf::RectangleShape arrow(sf::Vector2f(100, 200));
	sf::Texture arrows[3];
	arrows[0].loadFromFile("Images/Arrow1.png");
	arrows[1].loadFromFile("Images/Arrow2.png");
	arrows[2].loadFromFile("Images/Arrow3.png");


	const float  easing = 0.08f;
	window.clear();
	sf::Clock clock;
	// GAME CLOCK & TIMER
	sf::Clock clock2;
	int timer=0;
	int counter = 0;

	arrows[0].loadFromFile("Images/Arrow1.png");
	arrows[1].loadFromFile("Images/Arrow2.png");
	arrows[2].loadFromFile("Images/Arrow3.png");


	bumperTex.loadFromFile("Images/BumpB.png");
	
	bumperActiveTex1.loadFromFile("Images/Bump1B.png");
	bumperActiveTex2.loadFromFile("Images/Bump1.png");
	
	//Powerups
	PowerUps powerup;
	bool anim=false, available = true;
	int currentTime = 0;
	sf::String powerUps[] = { "Reduce gravity","Increase ball","Invisibility" };
	int nextPowerup = 0;

	//FLipper
	sf::Vector2f mirror(-1.0f, 1.0f);
	////Flipper
	Flipper flipper(sf::Vector2f(405, 600), sf::Vector2f(110, 10), 25.0f);
	Flipper flipper2(sf::Vector2f(615, 600), sf::Vector2f(110, 10), -25.0f, sf::Vector2f(0, 0), mirror);
	Flipper flipper3(sf::Vector2f(400, 100), sf::Vector2f(110, 10), -25.0f, sf::Vector2f(0, 25));
	Flipper flipper4(sf::Vector2f(620, 100), sf::Vector2f(110, 10), 25.0f, sf::Vector2f(0, 25), mirror);

	bool rolling = false;
	bool collided = false;
	bool hit1 = false, hit2 = false, hit3 = false, hit4 = false;
	float finalRotation1, finalRotation2, finalRotation3, finalRotation4;
	float rotation1 = flipper.flipper.getRotation(), rotation2 = flipper2.flipper.getRotation(),
		rotation3 = flipper3.flipper.getRotation(), rotation4 = flipper4.flipper.getRotation();
	const float acc = 0.01f;

	int winner = 0;
	int p1Score = 0;
	int p2Score = 0;
	sf::Font font;
	sf::Text Ltexts[5], Rtexts[4];
	sf::Text winnerText,helpText;
	if (!font.loadFromFile("Fonts/ubuntu.ttf"))
	{
		// handle error
	}
	for (int i = 0;i < 5;i++) {
		Ltexts[i].setFont(font);
		Ltexts[i].setFillColor(sf::Color::Red);
		Ltexts[i].setPosition(sf::Vector2f(20, 30+200*i));
	}

	for (int i = 0;i < 4;i++) {
		Rtexts[i].setFont(font);
		Rtexts[i].setFillColor(sf::Color::Red);
		Rtexts[i].setPosition(sf::Vector2f(800, 200+30*i));
	}
	winnerText.setFont(font);
	winnerText.setFillColor(sf::Color::Yellow);
	winnerText.setPosition(sf::Vector2f(200, 400));


	//SOUND
	sf::Music bumperSound, flipperSound,outSound;
	if (!bumperSound.openFromFile("Sounds/Bumper.wav"));
	if (!flipperSound.openFromFile("Sounds/Flipper.wav"));
	if (!outSound.openFromFile("Sounds/fall.wav"));

	//Main loop
	while (window.isOpen()) {
		window.clear();
		sf::Time dt = clock.restart();
		sf::Event event;
		/*elapsedTime += dt;*/
		hit1 = false;
		hit2 = false;
		hit3 = false;
		hit4 = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			finalRotation1 = 0.0f;
			rotation1 += easing * (finalRotation1 - rotation1);
			//std::cout << rotation << std::endl;
			flipper.flipper.setRotation(rotation1);
			flipper.sprite.setRotation(rotation1);
			flipperSound.play();
			hit1 = true;
		}
		else {
			finalRotation1 = 25.0f;
			rotation1 += easing * (finalRotation1 - rotation1);
			flipper.flipper.setRotation(rotation1);
			flipper.sprite.setRotation(rotation1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			finalRotation2 = 0.0f;
			flipperSound.play();
			rotation2 += easing * (finalRotation2 - rotation2);
			//std::cout << rotation << std::endl;
			flipper2.flipper.setRotation(rotation2);
			flipper2.sprite.setRotation(rotation2);
			hit2 = true;
		}
		else {
			finalRotation2 = -25.0f;
			rotation2 += easing * (finalRotation2 - rotation2);
			flipper2.flipper.setRotation(rotation2);
			flipper2.sprite.setRotation(rotation2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			finalRotation3 = 0.0f;
			rotation3 += easing * (finalRotation3 - rotation3);
			//std::cout << rotation << std::endl;
			flipper3.flipper.setRotation(rotation3);
			flipper3.sprite.setRotation(rotation3);
			hit3 = true;
			flipperSound.play();
		}
		else {
			finalRotation3 = -25.0f;
			rotation3 += easing * (finalRotation3 - rotation3);
			flipper3.flipper.setRotation(rotation3);
			flipper3.sprite.setRotation(rotation3);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			finalRotation4 = 0.0f;
			rotation4 += easing * (finalRotation4 - rotation4);
			//std::cout << rotation << std::endl;
			flipper4.flipper.setRotation(rotation4);
			flipper4.sprite.setRotation(rotation4);
			hit4 = true;
			flipperSound.play();
		}
		else {
			finalRotation4 = 25.0f;
			rotation4 += easing * (finalRotation4 - rotation4);
			flipper4.flipper.setRotation(rotation4);
			flipper4.sprite.setRotation(rotation4);
		}
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{
				case sf::Keyboard::S:
					if (!anim) {
						currentTime = timer;
						anim = true;
					}
					break;
				case sf::Keyboard::Down:
					if (!anim) {
						currentTime = timer;
						anim = true;
					}
					break;
					

					
				}
				if (event.type = sf::Event::KeyReleased) {
					switch (event.key.code)
					{
					case sf::Keyboard::A:
						hit1 = false;
						break;
					case sf::Keyboard::D:
						hit2 = false;
						break;
					case sf::Keyboard::Left:
						hit3 = false;
						break;
					case sf::Keyboard::Right:
						hit4 = false;
						break;
					}
				}
				if (event.key.code == sf::Keyboard::Escape)
					return;
				if (event.key.code == sf::Keyboard::Num1)
					ball.setParams(225, 300);
				if (event.key.code == sf::Keyboard::Num2)
					ball.setParams(225, 1000);
				if (event.key.code == sf::Keyboard::Num3)
					ball.setParams(315, 300);
				if (event.key.code == sf::Keyboard::Num4)
					ball.setParams(315, 1000);
			}
		}

		//Powerups
		if (timer-currentTime<10 && anim){
			available = false;
			if (nextPowerup%3==2)
				powerup.changeTransparency(ball, counter*64/100);
			/*if (nextPowerup % 3 == 1)
				powerup.changeRadius(ball, 16);
			if (nextPowerup % 3 == 0)
				powerup.changeRadius(ball, 6);

			if (timer - currentTime == 9) {
				nextPowerup += 1;
				powerup.resetBall(ball);
			}*/
		}
		else {
			currentTime = 0;
			anim = false;
			available = true;
		}

		////FlipperBL
		(checkCollision(ball, flipper, collided, hit1, rolling, window));
		(checkCollision(ball, flipper2, collided, hit2, rolling, window));
		(checkCollision(ball, flipper3, collided, hit3, rolling, window));
		(checkCollision(ball, flipper4, collided, hit4, rolling, window));



		//float dist1 = dist_ptl(sf::Vector2f(offset_x + resize * 154, 28 * resize), sf::Vector2f(offset_x + resize * 43, 361 * resize), ball);
		if (ball.globalPosition.y > window.getSize().y / 2)
			ball.GRAVITY = 200.0f;
		else
			ball.GRAVITY = -200.0f;





		for (int i = 0;i < 6;i++) {
			if (bumperIsActive[i]) {
				bumperBlinkCount[i]++;
				
				bumperBlinkCount[i] % 5 == 0 ? bumpers[i].shape.setTexture(&bumperActiveTex1) : bumpers[i].shape.setTexture(&bumperActiveTex2);
				if (bumperBlinkCount[i] == 100) {
					bumperIsActive[i] = false;
					bumperBlinkCount[i] = 0;
				}
			}
			else {
				bumpers[i].shape.setTexture(&bumperTex);
			}
			if (bumpers[i].collision(&ball)) {
				
				bumperSound.play();
				bumperIsActive[i] = true;
			}
		}

		//Pins
		for (int i = 0;i < pinNO;i++) {
			pins[i].collision(&ball);

		}
		
		


		//Draw to screen
		b.draw(window, ball);
		b.render(&window);
		flipper.render(window);
		flipper2.render(window);
		flipper3.render(window);
		flipper4.render(window);
	
	
		//TIMER
		timer = clock2.getElapsedTime().asSeconds();
		//arrow
		arrow.setTexture(&arrows[timer % 3]);
		ball.draw(dt);
		ball.render(&window);
		for (int i = 0;i < bumpNO;i++)
			bumpers[i].render(&window);
		for (int i = 0;i < pinNO;i++)
			pins[i].render(&window);
		

		//Display scores
		int mins, seconds;
		seconds = timer % 60;
		mins = timer / 60;
		Ltexts[0].setString("PLAYER 2: "+std::to_string(p2Score));
		if (seconds<10)
			Ltexts[1].setString(std::to_string(mins)+":0"+std::to_string(seconds));
		else
			Ltexts[1].setString(std::to_string(mins) +":"+ std::to_string(seconds));
		Ltexts[2].setString("PLAYER 1: "+std::to_string(p1Score));

		for (int i = 0; i < 3; i++)
		{
			window.draw(Ltexts[i]);
		}
		Rtexts[0].setString("Right Arrow");
		Rtexts[0].setCharacterSize(20);
		Rtexts[1].setString("D");
		for (int i = 0; i < 2; i++)
		{
			//window.draw(Rtexts[i]);
		}
		
		//0 to 100 counter
		counter += 1;
		if (counter > 100)
			counter = 0;
		window.display();
		//Check for points

		float dist7 = dist_ptl(sf::Vector2f(offset_x + resize * 262, 30 * resize), sf::Vector2f(offset_x + resize * 502, 30 * resize), ball);
		float dist8 = dist_ptl(sf::Vector2f(offset_x + resize * 262, 838 * resize), sf::Vector2f(offset_x + resize * 502, 832 * resize), ball);

		if (isCollided(dist7, ball))
		{
			outSound.play();
			p1Score++;
			//Reset code
			ball.reset(window, 1);
			//window.draw(text);
			//window.display();
			//sf::sleep(sf::Time(sf::milliseconds(1000)));

		}
		if (isCollided(dist8, ball))
		{
			outSound.play();
			p2Score++;
			//Reset code
			ball.reset(window, 2);


		}
		
		

		//Game over check
		switch (gameMode) {
		case 0:
			if (p1Score == 5)
				winner = 1;
			if (p2Score == 5)
				winner = 2;
			break;
		case 1:
			if (mins >= 2)
				p1Score > p2Score ? winner = 1 : winner = 2;
			break;
		}
		if (winner > 0) {
			winnerText.setString("The winner is : Player "+std::to_string(winner));
			window.draw(winnerText);
			window.display();
			sf::sleep(sf::Time(sf::milliseconds(5000)));
			break;
		}

		
		
	}

}
