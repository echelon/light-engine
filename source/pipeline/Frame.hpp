#ifndef LE_PIPELINE_FRAME
#define LE_PIPELINE_FRAME

#include "Geometry.hpp"
#include "MatrixStack.hpp"
#include "FrameBuffers.hpp"
#include "Tracking.hpp"
#include "../gfx/point.hpp"
#include <vector>
#include <memory>

/**
 * Implemenation of the drawing algorithm.
 */
namespace LE {
  class Frame {
	friend void FrameBuffers::setTracking(shared_ptr<Tracking>);

	public: 
	  /** More semantic */
	  enum FrameMode {
		SWAP,
		LASING,
		DRAWING
	  };

	  /** Modalities mostly within drawing phase. */
	  enum DrawingState {
		DRAWING_STATE_UNINITIALIZED,
		DRAWING_STATE_WRONG_MODE, // Mode = swap or lasing
		DRAWING_STATE_DRAWING_READY,
		DRAWING_STATE_DRAWING_NOW,
		DRAWING_STATE_DRAWING_FINISHED
	  };

	private:
	  /** Increment on instantiation. */
	  static int CREATE_COUNTER;

	protected:
	  /** Modality frame. */
	  FrameMode frameMode;
	  DrawingState drawingState;

	  /** For distinguishing FrameBuffers. */
	  unsigned int frameId;

	  /** Debugging calls. */
	  unsigned long numberBeginDrawCalls;
	  unsigned long numberDrawCalls;
	  unsigned long numberFinishCalls;
	  unsigned long numberGetPointsCalls;
	  unsigned long numberGotPointsCalls;

	  /** Counters on frame mode change. */
	  unsigned long countToModeSwap;
	  unsigned long countToModeLasing;
	  unsigned long countToModeDrawing;

	  /** The tracking algorithm to use. */
	  shared_ptr<Tracking> tracking;

	  /** Last point from the last draw (for tracking). */
	  Point lastPoint;
	  bool hasLastPoint; // TODO: C++14 std::optional<T>

	public:

	  Points points; // TODO/temp -- move back to protected

	  /** CTOR. */
	  Frame();

	  /** DTOR. */
	  ~Frame();

	  /** If the frame has any points in it. */
	  bool hasPoints() const;

	  unsigned int getNumberPoints() const;

	  /** Clear the frame buffer of points. */
	  void beginDrawing();

	  // XXX/Note: I pay little attention to this version. See next one.
	  /** Draw Geometry. */
	  void draw(const Geometry& geo, bool useTracking = true);

	  /** Draw Geometry with transformation. */
	  void draw(const Geometry& geo, const MatrixStack& matStack, 
		  bool useTracking = true);

	  /**
	   * Mark the drawing cycle as finished.
	   * For mode control and stats
	   */
	  void finishDrawing();

	  /** Set the frame mode. Controls other internal state. */
	  void setFrameMode(FrameMode mode);
	  FrameMode getFrameMode() const { return frameMode; };

	  void markGetPoints();
	  void markGotPoints(); // Non-looping / non-empty

	  // TODO: Inefficient
	  Points copyPoints() const;

	  /** Debug statistics */
	  void printStats() const;

	protected:
	  // XXX/FIXME: This is absolutely not threadsafe! 
	  // Call before drawing begins.
	  // TODO: I don't like having to sync state between frames.
	  // Perhaps drawing should be performed by another object.
	  void setTracking(shared_ptr<Tracking> tracking);
  };
}

#endif
