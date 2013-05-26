#include "tracking.hpp"
#include "../etherdream/types.hpp"

#include <iostream>
using namespace std;

Points calculate_tracking_pts(const Points& a, const Points& b,
	unsigned int num, const Color c) {
		return calculate_tracking_pts(a.back(), b[0], num, c);
}

Points calculate_tracking_pts(const Points& a, const Point& b,
	unsigned int num, const Color c) {
		return calculate_tracking_pts(a.back(), b, num, c);
}

Points calculate_tracking_pts(const Point& a, const Points& b,
	unsigned int num, const Color c) {
		return calculate_tracking_pts(a, b[0], num, c);
}

// TODO: Very unsophisticated
// TODO: Floating point math seems... slower than integer.
Points calculate_tracking_pts(const Point& a, const Point& b,
		unsigned int num, const Color c) 
{
	Points blankPts;
	
	float lastX = a.pos.x;
	float lastY = a.pos.y;
	float xDiff = lastX - b.pos.x;
	float yDiff = lastY - b.pos.y;

	for(unsigned int i = 0; i < num; i++) {
		float perc = i/(float)num;
		float xb = (float)(lastX - xDiff*perc);
		float yb = (float)(lastY - yDiff*perc);
		blankPts.push_back(Point(xb, yb, c.r, c.g, c.b));
		//blankPts.push_back(Point(xb, yb, CMAX, CMAX, CMAX));
	}

	return blankPts;
}
