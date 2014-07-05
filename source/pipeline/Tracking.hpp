#ifndef LE_PIPELINE_TRACKING
#define LE_PIPELINE_TRACKING

#include "../gfx/point.hpp"
#include "../gfx/color.hpp"
#include <memory>

using namespace std;

// TODO: std::shared_ptr... Really??
// TODO: Methods that set number of points, color, etc. probably
// should not be in the base class. Implementors might be truly dynamic.
namespace LE {
  /**
   * Tracking algorithms are used to track from one "object" to
   * another, or from one frame to another. This is a virtual class
   * so that other implementations may be used.
   */
  class Tracking {
  
	public: 
	  static const unsigned int DEFAULT_TRACKING_POINTS = 15;

	  /** Many CTORs. */
	  Tracking();

	  Tracking(unsigned int numberPoints);

	  Tracking(unsigned int objectPoints, unsigned int framePoints);

	  Tracking(unsigned int numberPoints, Color tracking);

	  Tracking(unsigned int objectPoints, unsigned int framePoints,
		  Color objectTracking, Color frameTracking);

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
	  static Points* doTrack(const Point& p1, const Point& p2, 
		  unsigned int trackingPoints, Color color);
  };
}
#endif
