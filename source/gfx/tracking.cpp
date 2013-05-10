#include "tracking.hpp"

Points calculate_tracking_pts(const Points& a, const Points& b) {
	return calculate_tracking_pts(a.back(), b[0]);
}

Points calculate_tracking_pts(const Points& a, const Point& b) {
	return calculate_tracking_pts(a.back(), b);
}

Points calculate_tracking_pts(const Point& a, const Points& b) {
	return calculate_tracking_pts(a, b[0]);
}

// TODO: Very unsophisticated
// TODO: Floating point math seems... slower than integer.
Points calculate_tracking_pts(const Point& a, const Point& b) 
{
	Points blankPts;
	
	float lastX = a.x;
	float lastY = a.y;
	float xDiff = lastX - b.x;
	float yDiff = lastY - b.y;

	for(unsigned int i = 0; i < TRACKING_SAMPLE_PTS; i++) {
		float perc = i/(float)TRACKING_SAMPLE_PTS;
		float xb = (float)(lastX - xDiff*perc);
		float yb = (float)(lastY - yDiff*perc);
		blankPts.push_back(Point(xb, yb, 10000.0f, 0.0f, 0.0f));
	}

	return blankPts;
}
