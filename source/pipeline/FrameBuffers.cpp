#include "FrameBuffers.hpp"
#include "Frame.hpp"
#include <iostream>
#include <assert.h>

using namespace std;

namespace LE {

  FrameBuffers::FrameBuffers(): 
	lasing(0),
	drawing(1),
	waiting(2),
	nextLasingFrameReady(false),
	numberDrawsComplete(0),
	numberLasesComplete(0),
	numberLasingSwaps(0)
  {
	frames = new std::shared_ptr<Frame>[3];

	// Lasing
	frames[lasing] = std::shared_ptr<Frame>(new Frame());
	frames[lasing]->setFrameMode(Frame::LASING);

	// Drawing
	frames[drawing] = std::shared_ptr<Frame>(new Frame());
	frames[drawing]->setFrameMode(Frame::DRAWING);

	// Waiting buffer
	frames[waiting] = std::shared_ptr<Frame>(new Frame());
  }

  FrameBuffers::~FrameBuffers() {
	// DTOR
  }

  std::shared_ptr<Frame> FrameBuffers::getLasingFrame() {
	mutex.lock();
	std::shared_ptr<Frame> frame = frames[lasing];
	assert(frame->getFrameMode() == Frame::LASING);
	mutex.unlock();
	return frame;
  }

  std::shared_ptr<Frame> FrameBuffers::getDrawingFrame() {
	mutex.lock();
	std::shared_ptr<Frame> frame = frames[drawing];
	assert(frame->getFrameMode() == Frame::DRAWING);
	mutex.unlock();
	return frame;
  }

  // TODO: Requires debug
  void FrameBuffers::doneDrawing() {
	mutex.lock();

	assert(frames[lasing]->getFrameMode() == Frame::LASING);
	assert(frames[drawing]->getFrameMode() == Frame::DRAWING);
	assert(frames[waiting]->getFrameMode() == Frame::SWAP);
	assert(drawing != lasing && lasing != waiting && 
		waiting != drawing);

	numberDrawsComplete++;
	nextLasingFrameReady = true;

	// Swap out roles
	unsigned int swap_ = waiting;
	waiting = drawing;
	drawing = swap_;
	frames[drawing]->setFrameMode(Frame::DRAWING);
	frames[waiting]->setFrameMode(Frame::SWAP);

	mutex.unlock();
  }

  void FrameBuffers::doneLasing() {
	mutex.lock();

	assert(frames[lasing]->getFrameMode() == Frame::LASING);
	assert(frames[drawing]->getFrameMode() == Frame::DRAWING);
	assert(frames[waiting]->getFrameMode() == Frame::SWAP);
	assert(drawing != lasing && lasing != waiting && 
		waiting != drawing);

	numberLasesComplete++;

	if (!nextLasingFrameReady) {
	  // We're not ready with the next frame
	  mutex.unlock();
	  return;
	}

	numberLasingSwaps++;
	nextLasingFrameReady = false;

	// Swap out roles
	unsigned int swap_ = lasing;
	lasing = waiting;
	waiting = swap_;
	frames[lasing]->setFrameMode(Frame::LASING);
	frames[waiting]->setFrameMode(Frame::SWAP);

	mutex.unlock();
  }

  void FrameBuffers::printSizes() const
  {
	// Non-locking
	cout 
	  << " lasing = "
	  << lasing
	  << " size = "
	  << frames[lasing]->getNumberPoints()
	  << endl
	  << " waiting = "
	  << waiting 
	  << " size = "
	  << frames[waiting]->getNumberPoints()
	  << endl
	  << " drawing = " 
	  << drawing 
	  << " size = "
	  << frames[drawing]->getNumberPoints()
	  << endl;
  }

  void FrameBuffers::printStats() const
  {
	// Non-locking
	cout 
	  << numberDrawsComplete
	  << " Draws | "
	  << numberLasesComplete
	  << " Lases ("
	  << numberLasingSwaps
	  << " novel frames)"
	  << endl;
  }

  void FrameBuffers::printFullStats() const
  {
	// Non-locking
	cout 
	  << numberDrawsComplete
	  << " Draws | "
	  << numberLasesComplete
	  << " Lases ("
	  << numberLasingSwaps
	  << " novel frames)"
	  << endl;

	for (unsigned int i = 0; i < 3; i++) {
	  cout << "  - ";
	  frames[i]->printStats();
	}
  }

} // end namespace LE

