#include "FrameBuffers.hpp"
#include "Frame.hpp"
#include <iostream>

using namespace std;

namespace LE {

  FrameBuffers::FrameBuffers(): 
	lasing(0),
	nextLasing(1),
	drawing(2),
	waiting(2),
	nextLasingFrameReady(false)
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
	mutex.lock();
	std::shared_ptr<Frame> frame = frames[lasing];
	mutex.unlock();
	return frame;
  }

  std::shared_ptr<Frame> FrameBuffers::getDrawingFrame() {
	mutex.lock();
	std::shared_ptr<Frame> frame = frames[drawing];
	mutex.unlock();
	return frame;
  }

  // TODO: Requires debug
  void FrameBuffers::doneDrawing() {
	mutex.lock();
	//unsigned int oldDrawing = drawing;

	unsigned int swap_ = nextLasing; // missed your chance
	//waiting = nextLasing; // missed your chance

	nextLasing = drawing; // now you're up instead
	drawing = swap_;

	nextLasingFrameReady = true;

	//waiting = oldDrawing;

	//drawing = waiting;

	mutex.unlock();
  }

  void FrameBuffers::doneLasing() {
	mutex.lock();

	if (!nextLasingFrameReady) {
	  // We're not ready with the next frame
	  mutex.unlock();
	  return;
	}

	cout << "SWAP IN DRAWING FRAME NOW..." << endl << endl;

	nextLasingFrameReady = false;

	unsigned int swap_ = lasing;
	lasing = nextLasing;
	nextLasing = swap_;

	/*if (lasing == nextLasing) {
	  // We're not ready with the next frame
	  mutex.unlock();
	  return;
	}*/

	// Swap
	//waiting = lasing; // TODO unconfirmed

	mutex.unlock();
  }

  void FrameBuffers::printSizes()
  {
	mutex.lock();
	cout 
	  << " lasing = "
	  << lasing
	  << " size = "
	  << frames[lasing]->getNumberPoints()
	  << endl
	  << " nextLasing = "
	  << nextLasing
	  << " size = "
	  << frames[nextLasing]->getNumberPoints()
	  << endl
	  << " drawing = " 
	  << drawing 
	  << " size = "
	  << frames[drawing]->getNumberPoints()
	  << endl;
	mutex.unlock();
  }

} // end namespace LE

