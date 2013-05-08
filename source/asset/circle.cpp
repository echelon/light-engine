#include "circle.hpp"
#include "../etherdream/types.hpp"
#include <math.h>

Points Circle::getPoints(unsigned int num)
{
	const double PI = 3.14159265;
	Points points;
	double np = (double)numPoints;

	for(unsigned int i = drawPosition; i < numPoints; i++) 
	{
		double j = 2 * PI * drawPosition / np;
		Point pt;

		drawPosition++;

		pt.x = (int)(cos(j) * radius);
		pt.y = (int)(sin(j) * radius);

		pt.r = CMAX;
		pt.g = CMAX;
		pt.b = CMAX;

		points.push_back(pt);

		if(points.size() >= num) {
			break;
		}
	}

	if(drawPosition >= numPoints) {
		drawPosition = 0;
		cout << "Reset circle" << endl;
	}

	return points;
}

Points Circle::getAllPoints()
{
	const double PI = 3.14159265;
	Points points;
	double np = (double)numPoints;

	for(unsigned int i = 0; i < numPoints; i++) 
	{
		double j = 2 * PI * drawPosition / np;
		Point pt;

		pt.x = (int)(cos(j) * radius);
		pt.y = (int)(sin(j) * radius);

		pt.r = CMAX;
		pt.g = CMAX;
		pt.b = CMAX;

		points.push_back(pt);
	}

	return points;
}
