#ifndef LE_PIPELINE_TRACKING
#define LE_PIPELINE_TRACKING

#include "../gfx/point.hpp"
#include <memory>

using namespace std;

// TODO: std::shared_ptr... Really??

namespace LE {
  /**
   * Tracking Algorithm Interface
   * Tracking algorithms are used to track from one "object" to
   * another, or from one frame to another.
   */
  class Tracking {
  
	public: 
	  /** DTOR if needed by implementors. */
	  virtual ~Tracking() {};

	  /** Generic tracking that does not distinguish intent. */
	  virtual shared_ptr<Points> track(const Point& p1,
		  const Point& p2) const = 0;

	  /** Track from one object to the next. */
	  virtual shared_ptr<Points> trackToObject(const Point& p1,
		  const Point& p2) const = 0;

	  /** Track from one frame to the start of the next. */
	  virtual shared_ptr<Points> trackToFrame(const Point& p1,
		  const Point& p2) const = 0; 
  };
}

#endif
