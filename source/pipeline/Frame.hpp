#ifndef LE_PIPELINE_FRAME
#define LE_PIPELINE_FRAME

#include <vector>
#include "../gfx/point.hpp"

/**
 * Implemenation of the drawing algorithm.
 */
namespace LE {

  class Frame {
	protected:
	  /** Point buffer. */
	  std::vector<Point> points;

	  /** Entities. */

	public:
	  /** CTOR. */
	  Frame();

	  /** DTOR. */
	  ~Frame();

	  /** 
	   * Synchronously calculate the frame and replace the buffer
	   * contents. 
	   */
	  void calculateFrame();

	  /**
	   * Synchronously calculate the frame and replace the buffer
	   * contents. Use the last frame as the start point for tracking.
	   */
	  void calculateFrame(const Frame& previousFrame);
  };
}

#endif
