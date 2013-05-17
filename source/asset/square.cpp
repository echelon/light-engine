#include "square.hpp"
#include "../etherdream/types.hpp"
#include "../gfx/color.hpp"
#include <math.h>

Points Square::getAllPoints() const
{
	Points points;
	Points pts;

	Point q1 = Point(-1.0, -1.0, color);
	Point q2 = Point(-1.0, 1.0, color);
	Point q3 = Point(1.0, 1.0, color);
	Point q4 = Point(1.0, -1.0, color);

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

Points Square::getEdge(Point v1, Point v2, unsigned int num) const
{
	Points points;

	float xDiff = v1.pos.x - v2.pos.x;
	float yDiff = v1.pos.y - v2.pos.y;

	for(unsigned int i = 0; i < num; i++) {
		float perc = i/(float)num;
		float xb = (float)(v1.pos.x - xDiff*perc);
		float yb = (float)(v1.pos.y - yDiff*perc);
		points.push_back(Point(xb, yb, color));
	}

	return points;
}
