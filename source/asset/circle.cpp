#include "circle.hpp"
#include "../etherdream/types.hpp"
#include "../gfx/color.hpp"
#include <math.h>

Points Circle::getAllPoints()
{
	const double PI = 3.14159265;
	Points points;
	double np = (double)numPoints;

	/*// Blanking in
	for(unsigned int i = 0; i < 15; i++) {
		double j = 2 * PI * i / np;
		int _x = (int)(cos(j) * radius) + pos.x;
		int _y = (int)(sin(j) * radius) + pos.y;
		points.push_back(Point(_x, _y, INVISIBLE));
	}*/

	// Generate circle
	for(unsigned int i = 0; i < numPoints; i++) 
	{
		double j = 2 * PI * i / np;
		Point pt;

		pt.pos.x = (int)(cos(j) * radius) + pos.x;
		pt.pos.y = (int)(sin(j) * radius) + pos.y;

		pt.color = color;

		points.push_back(pt);
	}

	/*// Blanking out
	for(unsigned int i = 0; i < 15; i++) {
		double j = 2 * PI * i / np;
		int _x = (int)(cos(j) * radius) + pos.x;
		int _y = (int)(sin(j) * radius) + pos.y;
		points.push_back(Point(_x, _y, INVISIBLE));
	}*/

	return points;
}

