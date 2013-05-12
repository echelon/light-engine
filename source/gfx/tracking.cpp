#include "tracking.hpp"
#include "../etherdream/types.hpp"

Points calculate_tracking_pts(const Points& a, const Points& b,
	unsigned int num) {
		return calculate_tracking_pts(a.back(), b[0], num);
}

Points calculate_tracking_pts(const Points& a, const Point& b,
	unsigned int num) {
		return calculate_tracking_pts(a.back(), b, num);
}

Points calculate_tracking_pts(const Point& a, const Points& b,
	unsigned int num) {
		return calculate_tracking_pts(a, b[0], num);
}

// TODO: Very unsophisticated
// TODO: Floating point math seems... slower than integer.
Points calculate_tracking_pts(const Point& a, const Point& b,
		unsigned int num) 
{
	Points blankPts;
	
	float lastX = a.x;
	float lastY = a.y;
	float xDiff = lastX - b.x;
	float yDiff = lastY - b.y;

	for(unsigned int i = 0; i < num; i++) {
		float perc = i/(float)num;
		float xb = (float)(lastX - xDiff*perc);
		float yb = (float)(lastY - yDiff*perc);
		blankPts.push_back(Point(xb, yb, 0, 0, 0));
		//blankPts.push_back(Point(xb, yb, CMAX, CMAX, CMAX));
	}

	return blankPts;
}
