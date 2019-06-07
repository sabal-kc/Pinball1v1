#pragma once
#include<SFML\Graphics.hpp>
class GeneralUtils
{
public:
	GeneralUtils();
	~GeneralUtils();
	static float dist(sf::Vector2f first, sf::Vector2f second);
	static sf::Vector2f closestpointonline(float lx1, float ly1,float lx2, float ly2, float x0, float y0);
};

