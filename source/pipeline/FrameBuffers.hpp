#ifndef LE_PIPELINE_FRAMEBUFFERS
#define LE_PIPELINE_FRAMEBUFFERS

#include <memory>
#include <mutex>

namespace LE {
  class Frame;
  class FrameBuffers {

	protected:
	  /** 
	   * Frames x3:
	   *  - Lasing frame 
	   *  - Drawing frame
	   *  - Waiting frame
	   */
	  std::shared_ptr<Frame>* frames;

	  /** Mutex guard on frame swap. */
	  std::mutex mutex;

	  /** Pointers to different frames. */
	  int lasing;
	  int drawing;
	  int waiting;

	public:
	  FrameBuffers();
	  ~FrameBuffers();
	
	  /** Get the current frame to lase. */
	  std::shared_ptr<Frame> getLasingFrame();

	  /** Get the current frame to draw on. */
	  std::shared_ptr<Frame> getDrawingFrame();

	  /** Denote finish of drawing. */
	  void doneDrawing();

	  /** Denote finish of lasing. */
	  void doneLasing();
  };
}

#endif
