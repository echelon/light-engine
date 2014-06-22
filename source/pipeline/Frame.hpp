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
	//friend class FrameBuffers;

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
	  /** Point buffer. */
	  // TODO: Make protected, not public
	  
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

	public:

	  Points points; // TODO/temp -- move back to protected

	  /** CTOR. */
	  Frame();

	  /** DTOR. */
	  ~Frame();

	  unsigned int getNumberPoints() const;

	  /** Clear the frame buffer of points. */
	  void beginDrawing();

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
	   * Mark the drawing cycle as finished.
	   * For mode control and stats
	   */
	  void finishDrawing();

	  /**
	   * Set the frame mode. Controls other internal state.
	   */
	  void setFrameMode(FrameMode mode);
	  FrameMode getFrameMode() const { return frameMode; };

	  void markGetPoints();
	  void markGotPoints(); // Non-looping / non-empty

	  // TODO: Inefficient
	  Points copyPoints() const;

	  /** Debug statistics */
	  void printStats() const;
  };
}

#endif
