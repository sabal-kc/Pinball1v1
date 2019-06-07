#include "GeneralUtils.h"



GeneralUtils::GeneralUtils()
{
}


GeneralUtils::~GeneralUtils()
{
}

float GeneralUtils::dist(sf::Vector2f first, sf::Vector2f second)
{
	return (pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

sf::Vector2f GeneralUtils::closestpointonline(float lx1, float ly1, float lx2, float ly2, float x0, float y0)
{
	float A1 = ly2 - ly1;
	float B1 = lx1 - lx2;
	double C1 = (ly2 - ly1)*lx1 + (lx1 - lx2)*ly1;
	double C2 = -B1*x0 + A1*y0;
	double det = A1*A1 - -B1*B1;
	double cx = 0;
	double cy = 0;
	if (det != 0) {
		cx = (float)((A1*C1 - B1*C2) / det);
		cy = (float)((A1*C2 - -B1*C1) / det);
	}
	else {
		cx = x0;
		cy = y0;
	}
	return sf::Vector2f(cx, cy);
}

