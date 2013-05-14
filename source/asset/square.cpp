#include "square.hpp"
#include "../etherdream/types.hpp"
#include "../gfx/color.hpp"
#include <math.h>

Points Square::getAllPoints()
{
	Points points;
	Points pts;

	float half = edge/2.0;

	Point q1 = Point(-half + x, -half + y, r, g, b);
	Point q2 = Point(-half + x, half + y, r, g, b);
	Point q3 = Point(half + x, half + y, r, g, b);
	Point q4 = Point(half + x, -half + y, r, g, b);

	for(unsigned int i = 0; i < numVertexPoints; i++) {
		points.push_back(q1);
	}

	pts = getEdge(q1, q2, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		points.push_back(pts[i]);
	}

	for(unsigned int i = 0; i < numVertexPoints; i++) {
		points.push_back(q2);
	}

	pts = getEdge(q2, q3, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		points.push_back(pts[i]);
	}

	for(unsigned int i = 0; i < numVertexPoints; i++) {
		points.push_back(q3);
	}	
	
	pts = getEdge(q3, q4, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		points.push_back(pts[i]);
	}
	
	for(unsigned int i = 0; i < numVertexPoints; i++) {
		points.push_back(q4);
	}	
	
	pts = getEdge(q4, q1, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		points.push_back(pts[i]);
	}

	return points;
}

Points Square::getEdge(Point v1, Point v2, int num) 
{
	Points points;

	float xDiff = v1.x - v2.x;
	float yDiff = v1.y - v2.y;

	for(unsigned int i = 0; i < num; i++) {
		float perc = i/(float)num;
		float xb = (float)(v1.x - xDiff*perc);
		float yb = (float)(v1.y - yDiff*perc);
		points.push_back(Point(xb, yb, r, g, b));
	}

	return points;
}
