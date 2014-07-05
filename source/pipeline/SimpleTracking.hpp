#ifndef LE_PIPELINE_SIMPLETRACKING
#define LE_PIPELINE_SIMPLETRACKING

#include "Tracking.hpp"
#include "../gfx/color.hpp"

using namespace std;

namespace LE {
  /**
   * Simple tracking with a constant number of points.
   */
  class SimpleTracking : public Tracking {
  
	public: 
	  static const unsigned int DEFAULT_TRACKING_POINTS = 15;

	  /** Many CTORs. */
	  SimpleTracking();

	  SimpleTracking(unsigned int numberPoints);

	  SimpleTracking(unsigned int objectPoints, unsigned int framePoints);

	  SimpleTracking(unsigned int numberPoints, Color tracking);

	  SimpleTracking(unsigned int objectPoints, unsigned int framePoints,
		  Color objectTracking, Color frameTracking);

	  virtual ~SimpleTracking() {
		cout << "DTOR ~SimpleTracking()" << endl;
	  }

	  virtual void foo() const {
		cout << "SimpleTracking::foo()" << endl;
	  }

	  /** Generic tracking that does not distinguish intent. */
	  virtual shared_ptr<Points> track(const Point& p1,
		  const Point& p2) const;

	  /** Track from one object to the next. */
	  virtual shared_ptr<Points> trackToObject(const Point& p1,
		  const Point& p2) const;

	  /** Track from one frame to the start of the next. */
	  virtual shared_ptr<Points> trackToFrame(const Point& p1,
		  const Point& p2) const;

	protected:
	  /** A constant number of points to add. */
	  unsigned int numberObjectPoints;
	  unsigned int numberFramePoints;

	  /** 
	   * Blanking colors.
	   * Typically the laser is off, but can be useful for debugging.
	   */
	  Color objectTrackingColor;
	  Color frameTrackingColor;

	  /** Internal algorithm implementation. */
	  Points* doTrack(const Point& p1, const Point& p2, 
		  unsigned int trackingPoints, Color color) const;
  };
}

#endif
