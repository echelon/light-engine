#include "Tracking.hpp"
#include "../etherdream/types.hpp"
#include <iostream>


namespace LE {

  shared_ptr<Points> Tracking::track(const Point& p1, 
	  const Point& p2) const {
	float lastX = p1.pos.x;
	float lastY = p1.pos.y;
	float xDiff = p1.pos.x - p2.pos.x;
	float yDiff = p1.pos.y - p2.pos.y;
	float divisor = numberPoints;

	shared_ptr<Points> pts(new Points);
	pts->reserve(numberPoints);

	for (unsigned int i = 0; i < numberPoints; i++) {
	  float percent = i / divisor;
	  float xb = lastX - xDiff * percent;
	  float yb = lastY - yDiff * percent;

	  /*cout << "Tracking (" 
		<< i 
		<< ") x: " 
		<< xb << " y: " 
		<< yb 
		<< endl;*/

	  pts->push_back(Point(xb, yb, CMAX, CMAX, 0));
	}
	return pts;
  }

  shared_ptr<Points> Tracking::trackToObject(const Point& p1, 
	  const Point& p2) const {
	return track(p2, p2);
  }

  shared_ptr<Points> Tracking::trackToFrame(const Point& p1, 
	  const Point& p2) const {
	return track(p2, p2);
  }

} // end namespace LE
