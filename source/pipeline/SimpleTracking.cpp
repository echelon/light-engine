#include "SimpleTracking.hpp"
#include "../etherdream/types.hpp"

namespace LE {

  SimpleTracking::SimpleTracking() :
	  numberObjectPoints(DEFAULT_TRACKING_POINTS),
	  numberFramePoints(DEFAULT_TRACKING_POINTS),
	  objectTrackingColor(INVISIBLE),
	  frameTrackingColor(INVISIBLE)
	  {}

  SimpleTracking::SimpleTracking(unsigned int numPoints) :
	  numberObjectPoints(numPoints),
	  numberFramePoints(numPoints),
	  objectTrackingColor(INVISIBLE),
	  frameTrackingColor(INVISIBLE)
	  {}

  SimpleTracking::SimpleTracking(unsigned int objPts, 
	  unsigned int framePts) :
		  numberObjectPoints(objPts),
		  numberFramePoints(framePts),
		  objectTrackingColor(INVISIBLE),
		  frameTrackingColor(INVISIBLE)
		  {}

  SimpleTracking::SimpleTracking(unsigned int numPoints, Color tracking) :
	  numberObjectPoints(numPoints),
	  numberFramePoints(numPoints),
	  objectTrackingColor(tracking),
	  frameTrackingColor(tracking)
	  {}

  SimpleTracking::SimpleTracking(unsigned int objPts, 
	  unsigned int framePts, Color objColor, Color frameColor) :
		  numberObjectPoints(objPts),
		  numberFramePoints(framePts),
		  objectTrackingColor(objColor),
		  frameTrackingColor(frameColor)
		  {}

  shared_ptr<Points> SimpleTracking::track(const Point& p1, 
	  const Point& p2) const {
	return shared_ptr<Points>(doTrack(p1, p2, numberObjectPoints,
	    objectTrackingColor));
  }

  shared_ptr<Points> SimpleTracking::trackToObject(const Point& p1, 
	  const Point& p2) const {
	return shared_ptr<Points>(doTrack(p1, p2, numberObjectPoints,
		  objectTrackingColor));
  }

  shared_ptr<Points> SimpleTracking::trackToFrame(const Point& p1, 
	  const Point& p2) const {
	return shared_ptr<Points>(doTrack(p1, p2, numberFramePoints,
	    frameTrackingColor));
  }

  Points* SimpleTracking::doTrack(const Point& p1, const Point& p2, 
	  unsigned int trackingPoints, Color color) const {
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

