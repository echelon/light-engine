#ifndef LE_PIPELINE_FRAME
#define LE_PIPELINE_FRAME

#include <vector>
#include "../gfx/point.hpp"
#include "Geometry.hpp"
#include "MatrixStack.hpp"

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
	  
	  /** Drawing mode of the frame. */
	  Mode mode;

	public:

	  Points points; // TODO/temp -- move back to protected

	  /** CTOR. */
	  Frame();

	  /** DTOR. */
	  ~Frame();

	  /** Can I haz read permissions? */
	  bool canRead() const {
		switch(mode) {
		  case READ:
		  case READ_WRITE:
			return true;
		  case NONE:
		  case WRITE:
			break;
		}
		return false;
	  };

	  /** Can I haz write permissions? */
	  bool canWrite() const {
		switch(mode) {
		  case WRITE:
		  case READ_WRITE:
			return true;
		  case NONE:
		  case READ:
			break;
		}
		return false;
	  };

	unsigned int getNumberPoints() const;

    /**
	 * Draw Geometry.
	 */
	void draw(const Geometry& geo);
	// void draw_notrack() for non-tracking/blanking

	/**
	 * Draw Geometry with transformation.
	 */
	void draw(const Geometry& geo, const MatrixStack& matStack);

	/**
	 * Clear the frame buffer of points.
	 */
	void clear();

	// TODO: Inefficient
	Points getPoints() const;
  };
}

#endif
