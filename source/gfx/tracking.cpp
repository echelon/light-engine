#include "tracking.hpp"

// TODO: Very unsophisticated
// TODO: Floating point math seems... slower than integer.
Points calculate_tracking_pts(const Points& a, const Points& b) 
{
	Points blankPts;
	
	float lastX = a.back().x;
	float lastY = a.back().y;
	float xDiff = lastX - b[0].x;
	float xDiff = lastY - b[0].y;

	for(unsigned int i = 0; i < TRACKING_SAMPLE_PTS; i++) {
		float perc = i/(float)TRACKING_SAMPLE_PTS;
		float xb = (float)(lastX - xDiff*perc);
		float xb = (float)(lastY - yDiff*perc);
		blankPts.push_back(Point(xb, yb, 0.0f, 0.0f, 0.0f));
	}

	return blankPts;
}
