#include "Tracking.hpp"
#include "../etherdream/types.hpp"
#include <iostream>

namespace LE {

  Tracking::Tracking() :
	  numberObjectPoints(DEFAULT_TRACKING_POINTS),
	  numberFramePoints(DEFAULT_TRACKING_POINTS),
	  objectTrackingColor(INVISIBLE),
	  frameTrackingColor(INVISIBLE)
	  {}

  Tracking::Tracking(unsigned int numPoints) :
	  numberObjectPoints(numPoints),
	  numberFramePoints(numPoints),
	  objectTrackingColor(INVISIBLE),
	  frameTrackingColor(INVISIBLE)
	  {}

  Tracking::Tracking(unsigned int objPts, unsigned int framePts) :
	  numberObjectPoints(objPts),
	  numberFramePoints(framePts),
	  objectTrackingColor(INVISIBLE),
	  frameTrackingColor(INVISIBLE)
	  {}

  Tracking::Tracking(unsigned int numPoints, Color tracking) :
	  numberObjectPoints(numPoints),
	  numberFramePoints(numPoints),
	  objectTrackingColor(tracking),
	  frameTrackingColor(tracking)
	  {}

  Tracking::Tracking(unsigned int objPts, unsigned int framePts, 
	  Color objColor, Color frameColor) :
		  numberObjectPoints(objPts),
		  numberFramePoints(framePts),
		  objectTrackingColor(objColor),
		  frameTrackingColor(frameColor)
		  {}

  shared_ptr<Points> Tracking::track(const Point& p1, 
	  const Point& p2) const {
	return shared_ptr<Points>(doTrack(p1, p2, numberObjectPoints,
	    objectTrackingColor));
  }

  shared_ptr<Points> Tracking::trackToObject(const Point& p1, 
	  const Point& p2) const {
	return shared_ptr<Points>(doTrack(p1, p2, numberObjectPoints,
	    objectTrackingColor));
  }

  shared_ptr<Points> Tracking::trackToFrame(const Point& p1, 
	  const Point& p2) const {
	return shared_ptr<Points>(doTrack(p1, p2, numberFramePoints,
	    frameTrackingColor));
  }

  Points* Tracking::doTrack(const Point& p1, const Point& p2, 
	  unsigned int trackingPoints, Color color) {
	float lastX = p1.pos.x;
	float lastY = p1.pos.y;
	float xDiff = p1.pos.x - p2.pos.x;
	float yDiff = p1.pos.y - p2.pos.y;
	float divisor = trackingPoints;

	Points* pts = new Points();
	pts->reserve(trackingPoints); // TODO: More efficient pre-alloc?

	for (unsigned int i = 0; i < trackingPoints; i++) {
	  float percent = i / divisor;
	  float x = lastX - xDiff * percent;
	  float y = lastY - yDiff * percent;

	  pts->push_back(Point(x, y, color));
	}
	return pts;
  }

} // end namespace LE
