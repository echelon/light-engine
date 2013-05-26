#include "circle.hpp"
#include "../etherdream/types.hpp"
#include "../gfx/color.hpp"
#include <math.h>
#include <memory>

void Circle::generateStaticPoints()
{
	const double PI = 3.14159265;
	Points points;
	double np = (double)numPoints;

	staticPoints = unique_ptr<Points>(new Points());

	// Generate circle
	for(unsigned int i = 0; i < numPoints; i++) 
	{
		double j = 2 * PI * i / np;
		Point pt;

		// Radius is understood to be '1.0' (unit circle)
		pt.pos.x = cos(j);
		pt.pos.y = sin(j);

		pt.color = color;

		staticPoints->push_back(pt);
	}
}
