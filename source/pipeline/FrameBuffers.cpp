#include "FrameBuffers.hpp"
#include "Frame.hpp"

namespace LE {

  FrameBuffers::FrameBuffers(): 
	lasing(0),
	nextLasing(0),
	drawing(1),
	waiting(2)
  {
	frames = new std::shared_ptr<Frame>[3];
	frames[0] = std::shared_ptr<Frame>(new Frame());
	frames[1] = std::shared_ptr<Frame>(new Frame());
	frames[2] = std::shared_ptr<Frame>(new Frame());

	frames[0]->mode = Frame::READ;
	frames[1]->mode = Frame::WRITE;
	frames[2]->mode = Frame::NONE;
  }

  FrameBuffers::~FrameBuffers() {
  }

  std::shared_ptr<Frame> FrameBuffers::getLasingFrame() {
	return frames[lasing];
  }

  std::shared_ptr<Frame> FrameBuffers::getDrawingFrame() {
	return frames[drawing];
  }

  // TODO: Requires debug
  void FrameBuffers::doneDrawing() {
	mutex.lock();
	unsigned int oldDrawing = drawing;

	nextLasing = oldDrawing;
	waiting = oldDrawing;

	drawing = waiting;

	mutex.unlock();
  }

  void FrameBuffers::doneLasing() {
	mutex.lock();

	if (lasing == nextLasing) {
	  // We're not ready with the next frame
	  mutex.unlock();
	  return;
	}

	// Swap
	lasing = nextLasing;
	mutex.unlock();
  }

} // end namespace LE

