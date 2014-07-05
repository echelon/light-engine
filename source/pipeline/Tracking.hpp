#ifndef LE_PIPELINE_TRACKING
#define LE_PIPELINE_TRACKING

#include "../gfx/point.hpp"
#include <memory>
#include <iostream>

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
	  Tracking() {
		cout << "Tracking() CTOR" << endl;
	  };

	  virtual ~Tracking() {
		cout << "~Tracking() DTOR" << endl;
	  };

	  virtual void foo() const {
		cout << "Tracking::foo()" << endl;
	  };

	  /** Generic tracking that does not distinguish intent. */
	  virtual shared_ptr<Points> track(const Point& p1,
		  const Point& p2) const {
		cout << "Tracking::track()" << endl;
		return shared_ptr<Points>(new Points());
	  };

	  /** Track from one object to the next. */
	  virtual shared_ptr<Points> trackToObject(const Point& p1,
		  const Point& p2) const {
		cout << "Tracking::trackToObject()" << endl;
		return shared_ptr<Points>(new Points());
	  };

	  /** Track from one frame to the start of the next. */
	  virtual shared_ptr<Points> trackToFrame(const Point& p1,
		  const Point& p2) const {
		cout << "Tracking::trackToFrame()" << endl;
		return shared_ptr<Points>(new Points());
	  };
  };
}

#endif
