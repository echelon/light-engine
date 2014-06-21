#ifndef LE_PIPELINE_FRAMEBUFFERS
#define LE_PIPELINE_FRAMEBUFFERS

#include <memory>
#include <mutex>

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
	  std::shared_ptr<Frame>* frames;

	  /** Indices to different frames. */
	  unsigned int lasing;
	  unsigned int nextLasing;
	  unsigned int drawing;
	  unsigned int waiting;

	  /** Whether the next lasing frame is ready. */
	  bool nextLasingFrameReady;

	  /** Mutex guard on frame swap. */
	  std::mutex mutex;

	public:
	  FrameBuffers();
	  ~FrameBuffers();
	
	  /** Get the current frame to lase. */
	  std::shared_ptr<Frame> getLasingFrame();

	  /** Get the current frame to draw on. */
	  std::shared_ptr<Frame> getDrawingFrame();

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
	  void printSizes();
  };
}

#endif
