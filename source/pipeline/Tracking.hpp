#ifndef LE_PIPELINE_TRACKING
#define LE_PIPELINE_TRACKING

#include "../gfx/point.hpp"
#include <memory>

using namespace std;

// TODO: Do a similar set of functions with Points instead of Point.
namespace LE {
  /**
   * Tracking algorithms are used to track from one "object" to
   * another, or from one frame to another. This is a virtual class
   * so that other implementations may be used.
   */
  class Tracking {
	public: 
	  /** Generic tracking that does not distinguish intent. */
	  virtual shared_ptr<Points> track(const Point& p1,
		  const Point& p2) const;

	  /** Track from one object to the next. */
	  virtual shared_ptr<Points> trackToObject(const Point& p1,
		  const Point& p2) const;

	  /** Track from one frame to the start of the next. */
	  virtual shared_ptr<Points> trackToFrame(const Point& p1,
		  const Point& p2) const;
  };
}
#endif
