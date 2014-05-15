#ifndef LE_PIPELINE_FRAME
#define LE_PIPELINE_FRAME

#include <vector>
#include "../gfx/point.hpp"

/**
 * Implemenation of the drawing algorithm.
 */
namespace LE {
  class Frame {
	friend class FrameBuffers;

	/** 
	 * Drawing mode bestows read, write, read-write, or no 
	 * permissions.
	 */
	enum Mode {
	  NONE,
	  READ,
	  WRITE,
	  READ_WRITE
	};

	protected:
	  /** Point buffer. */
	  std::vector<Point> points;
	  
	  /** Drawing mode of the frame. */
	  Mode mode;

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

	  /** Can I haz read permissions? */
	  bool canRead() const {
		switch(mode) {
		  case READ:
		  case READ_WRITE:
			return true;
		  case NONE:
		  case WRITE:
			return false;
		}
	  };

	  /** Can I haz write permissions? */
	  bool canWrite() const {
		switch(mode) {
		  case WRITE:
		  case READ_WRITE:
			return true;
		  case NONE:
		  case READ:
			return false;
		}
		return false;
	  };
  };
}

#endif
