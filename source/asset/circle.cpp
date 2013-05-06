#include "circle.hpp"
#include "../etherdream/types.hpp"
#include <math.h>

vector<Point> Circle::getPoints(unsigned int num)
{
	const double PI = 3.14159265;
	vector<Point> points;

	// numPoints points are in the circle
	
	for(unsigned int i = position; i < numPoints; i++) 
	{
		double j = 2 * PI * position / (double)numPoints;
		Point pt;

		position = (position + 1) % numPoints;

		pt.x = (int)(cos(j) * radius);
		pt.y = (int)(sin(j) * radius);

		//cout << "x,y: " << pt.x << ", " << pt.y << ", " << CMAX << endl;
		pt.r = CMAX;
		pt.g = CMAX;
		pt.b = CMAX;
		points.push_back(pt);

		if(points.size() > num) {
			break;
		}
	}

	cout << "Circle pts: " << points.size() << endl;

	return points;
}
