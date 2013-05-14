#include "circle.hpp"
#include "../etherdream/types.hpp"
#include "../gfx/color.hpp"
#include <math.h>

Points Circle::getAllPoints()
{
	const double PI = 3.14159265;
	Points points;
	double np = (double)numPoints;


	// Blanking in
	for(unsigned int i = 0; i < 15; i++) {
		double j = 2 * PI * i / np;
		int _x = (int)(cos(j) * radius) + x;
		int _y = (int)(sin(j) * radius) + y;
		points.push_back(Point(_x, _y, INVISIBLE));
	}

	// Generate circle
	for(unsigned int i = 0; i < numPoints; i++) 
	{
		double j = 2 * PI * i / np;
		Point pt;

		pt.x = (int)(cos(j) * radius) + x;
		pt.y = (int)(sin(j) * radius) + y;

		pt.r = r;
		pt.g = g;
		pt.b = b;

		points.push_back(pt);
	}

	// Blanking out
	for(unsigned int i = 0; i < 15; i++) {
		double j = 2 * PI * i / np;
		int _x = (int)(cos(j) * radius) + x;
		int _y = (int)(sin(j) * radius) + y;
		points.push_back(Point(_x, _y, INVISIBLE));
	}


	return points;
}

