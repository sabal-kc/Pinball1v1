#pragma once
#include "Ball.h"
#include "BumperObstacle.h"
#include "GeneralUtils.h"
#include "Flipper.h"
#include "PowerUps.h"
#include "Vector.h"
#include "Board.h"
#include <fstream>
#include <iostream>
class GameLoop
{
public:
	const float resize = 0.8073;
	float easing = 0.5f;
	float rotation = 30.0f;
	float finalRotation = 30.0f;
	int pinNO = 16, bumpNO = 6;
	
	

	
public:
	GameLoop();
	~GameLoop();
	void run(sf::RenderWindow& window, int gameMode);
};

