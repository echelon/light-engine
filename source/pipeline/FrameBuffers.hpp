#ifndef LE_PIPELINE_FRAMEBUFFERS
#define LE_PIPELINE_FRAMEBUFFERS

#include "Tracking.hpp"
#include <memory>
#include <mutex>

using namespace std;

namespace LE {
  class Frame;
  class FrameBuffers {

	protected:
	  /** 
	   * Frames x 3:
	   *  - Lasing frame 
	   *  - Drawing frame
	   *  - Waiting frame
	   */
	  shared_ptr<Frame> frames [3];

	  /** Indices to different frames. */
	  unsigned int lasing;
	  unsigned int drawing;
	  unsigned int waiting;

	  /** Whether the next lasing frame is ready. */
	  bool nextLasingFrameReady;

	  /** Stats on the number of done*() calls made. */
	  unsigned long numberDrawsComplete;
	  unsigned long numberLasesComplete;

	  /** Number of swaps in lasing frames. */
	  unsigned long numberLasingSwaps;

	  /** Mutex guard on frame swap. */
	  mutable std::mutex mutex;

	public:
	  FrameBuffers();
	  ~FrameBuffers();

	  // TODO: This feels awkward having to pass this to Frame.
	  // Perhaps frames themselves should be entirely hidden.
	  
	  void setTracking(shared_ptr<Tracking> tracking);
	
	  /** Get the current frame to lase. */
	  shared_ptr<Frame> getLasingFrame() const;

	  /** Get the current frame to draw on. */
	  shared_ptr<Frame> getDrawingFrame() const;

	  /** 
	   * Denote finish of drawing. 
	   * You **MUST** get a new drawing frame with getDrawingFrame()
	   */
	  void doneDrawing();

	  /** 
	   * Denote finish of lasing. 
	   * You **MUST** get a new lasing frame with getLasingFrame()
	   */
	  void doneLasing();

	  // Debug
	  void printSizes() const;
	  void printStats() const;
	  void printFullStats() const;
  };
}

#endif
