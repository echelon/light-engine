#include "rectangle.hpp"
#include "../etherdream/types.hpp"
#include "../gfx/color.hpp"
#include <math.h>
#include <memory>

void Rectangle::generateStaticPoints()
{
	Points pts;
	staticPoints = unique_ptr<Points>(new Points());

	for(unsigned int i = 0; i < numVertexPoints; i++) {
		staticPoints->push_back(Point(q1, color));
	}

	pts = getEdge(q1, q2, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		staticPoints->push_back(pts[i]);
	}

	for(unsigned int i = 0; i < numVertexPoints; i++) {
		staticPoints->push_back(Point(q2, color));
	}

	pts = getEdge(q2, q3, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		staticPoints->push_back(pts[i]);
	}

	for(unsigned int i = 0; i < numVertexPoints; i++) {
		staticPoints->push_back(Point(q3, color));
	}	
	
	pts = getEdge(q3, q4, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		staticPoints->push_back(pts[i]);
	}
	
	for(unsigned int i = 0; i < numVertexPoints; i++) {
		staticPoints->push_back(Point(q4, color));
	}	
	
	pts = getEdge(q4, q1, numEdgePoints);
	for(unsigned int i = 0; i < pts.size(); i++) {
		staticPoints->push_back(pts[i]);
	}
}

Points Rectangle::getEdge(Point v1, Point v2, unsigned int num) const
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
