#include "FrameBuffers.hpp"
#include "Frame.hpp"

namespace LE {

  FrameBuffers::FrameBuffers(): 
	lasing(0),
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
	return frames[0]; // TODO
  }

  std::shared_ptr<Frame> FrameBuffers::getDrawingFrame() {
	return frames[0]; // TODO 
  }

  void FrameBuffers::doneDrawing() {
	mutex.lock();
	mutex.unlock();
  }

  void FrameBuffers::doneLasing() {
	mutex.lock();
	mutex.unlock();
  }

} // end namespace LE

