#include "BumperObstacle.h"
#include <iostream>
#include "GeneralUtils.h"




BumperObstacle::BumperObstacle()
{

}

BumperObstacle::BumperObstacle(sf::Vector2f position, sf::Color color)
{
	center = position;
	shape.setRadius(RADIUS);
	shape.setPosition(position);
	shape.setOrigin(RADIUS, RADIUS);
	shape.setFillColor(color);
}



BumperObstacle::~BumperObstacle()
{
}

void BumperObstacle::draw()
{
	std::cout << "Draw called" << std::endl;
}

void BumperObstacle::render(sf::RenderWindow * window)
{
	window->draw(shape);
}

bool BumperObstacle::collision(Ball* ball)
{
	bool collided = (GeneralUtils::dist(center, ball->globalPosition) <= (RADIUS + ball->radius)*(RADIUS + ball->radius));
	if (collided) {
		// Distance between ball centers
		float fDistance = sqrt(GeneralUtils::dist(ball->globalPosition, this->center));
		// Calculate displacement required
		float fOverlap = 0.9f * (fDistance - ball->radius - this->RADIUS);
		// Normal
		float nx = (ball->globalPosition.x - this->center.x) / fDistance;
		float ny = (this->center.y - ball->globalPosition.y) / fDistance;
		// Tangent
		float tx = -ny;
		float ty = nx;
		// Dot Product Tangent
		float dpTan1 = ball->xVelocity * tx + ball->yVelocity * ty;
		// Dot Product Normal
		float dpNorm1 = ball->xVelocity * nx + ball->yVelocity * ny;
		float dpNorm2 = 0;
		// Conservation of momentum in 1D
		float m1 = (dpNorm1 * (mass1 - mass2) + 2.0f * mass2 * dpNorm2) / (mass1 + mass2);

		// Update ball velocities
		float newVelX1 = tx * dpTan1 + nx * m1;
		//float newVelX1 = tx * dpTan1;
		float newVelY1 = ty * dpTan1 + ny * m1;
		//float newVelY1 = ty * dpTan1;
		ball->changePosition(sf::Vector2f(-fOverlap * (ball->globalPosition.x - this->center.x) / fDistance,
			-fOverlap * (ball->globalPosition.y - this->center.y) / fDistance));
		ball->setParams2(newVelX1, newVelY1);
		
	}
	return collided;
}

void BumperObstacle::lightEffectsDraw()
{
	sf::Texture lightTexture;
	struct Light
	{
		sf::Vector2f position;
		sf::Vector2f scale;
		sf::Color color;
		Light(sf::Vector2f nposition, sf::Vector2f nscale, sf::Color ncolor) :
			position(nposition),
			scale(nscale),
			color(ncolor)
		{
		}
	};
	sf::RenderTexture lightMapTexture;
	lightMapTexture.create(1200, 700); // Make a lightmap that can cover our screen

	lightmap.setTexture(lightMapTexture.getTexture()); // Make our lightmap sprite use the correct texture
	lightTexture.loadFromFile("Images/biglight.png"); // Load in our light 
	lightTexture.setSmooth(true); // (Optional) It just smoothes the light out a bit
	light.setTexture(lightTexture); // Make our lightsprite use our loaded image
	light.setTextureRect(sf::IntRect(0, 0, 512, 512)); // Set where on the image we will take the sprite (X position, Y position, Width, Height)
	light.setOrigin(256.f, 256.f); // This will offset where we draw our ligts so the center of the light is right over where we want our light to be
	std::vector<Light> lights; // Contains all the lights
	lights.push_back(Light(sf::Vector2f(this->center.x, this->center.y), sf::Vector2f(0.1f, 0.1f), sf::Color(0, 255, 59, 255)));


	lightmap.setTextureRect(sf::IntRect(0, 0, 1200, 700)); // What from the lightmap we will draw
	lightmap.setPosition(0, 0); // Where on the backbuffer we will draw
								// Clear the buffer where we draw the lights, this color could be changed depending on the time of day in the game to show a night/daytime cycle
	lightMapTexture.clear(sf::Color(50, 50, 80, 240));
	// Loop over the lights in the vector
	for (std::size_t i = 0; i < lights.size(); ++i)
	{
		// Set the attributes of the light sprite to those of the current light
		light.setScale(lights[i].scale);
		light.setColor(lights[i].color);
		light.setPosition(lights[i].position);

		//Draw it to the lightmap
		lightMapTexture.draw(light, sf::BlendAdd); // This blendmode is used so the black in our lightimage won't be drawn to the lightmap
	}
	lightMapTexture.display(); // Need to make sure the rendertexture is displayed
}

void BumperObstacle::lightEffectsRender(sf::RenderWindow * window)
{
	window->draw(light);
	window->draw(lightmap, sf::BlendMultiply); // This blendmode is used to add the darkness from the lightmap with the parts where we draw ur light image show up brighter
}

void BumperObstacle::setPosColor(sf::Vector2f position, sf::Color color)
{
	center = position;
	shape.setRadius(RADIUS);
	shape.setPosition(position);
	shape.setOrigin(RADIUS, RADIUS);
	shape.setFillColor(color);
}

