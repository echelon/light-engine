#include "StreamingPointBuffer.hpp"
#include <assert.h>
#include <iostream>
#include <exception>

using namespace std;

namespace LE {

  const unsigned int StreamingPointBuffer::DEFAULT_SIZE = 200000;

  StreamingPointBuffer::StreamingPointBuffer() : 
	capacityLimit(DEFAULT_SIZE),
	allocation(DEFAULT_SIZE + 1),
	head(0),
	tail(0)
  {
	// TODO What about reserve() ?
	pointBuffer.resize(allocation); // Empty slot
  }

  StreamingPointBuffer::StreamingPointBuffer(unsigned int sizeCapacity) :
	capacityLimit(sizeCapacity),
	allocation(sizeCapacity + 1),
	head(0),
	tail(0)
  {
	pointBuffer.resize(allocation); // Empty slot
  }

  StreamingPointBuffer::~StreamingPointBuffer() {
	// TODO
  }

  void StreamingPointBuffer::add(
	  shared_ptr<vector<dac_point>> points) 
  {
	unsigned int numAdded = points->size();
	assert(numAdded <= capacityLimit);

	for (dac_point p: *points) {
	  pointBuffer[tail] = p; //dac_point(p);
	  tail = (tail + 1) % allocation;
	}

	// Ring buffer is full, overwrite old
    if (tail == head) {
	  head = (head + 1) % allocation;
	}
  }

  unique_ptr<vector<dac_point>> StreamingPointBuffer::get(
	  unsigned int numPoints) 
  {
	assert(numPoints > 0);
	assert(numPoints <= capacityLimit);

	vector<dac_point>* outPts = new vector<dac_point>;
	vector<dac_point>& outPtsRef = *outPts;

	outPts->reserve(numPoints);

	// TODO: Not most efficient copy.
	for (unsigned int i = 0; i < numPoints; i++) {
	  outPtsRef.push_back(pointBuffer[head]);
	  head = (head + 1) % allocation;
	}

	return unique_ptr<vector<dac_point>>(outPts);
  }

  bool StreamingPointBuffer::isEmpty() const {
	return head == tail;
  }

  bool StreamingPointBuffer::isFull() const {
	return (tail + 1) % allocation == head;
  }

  // TODO: Verify index math
  unsigned int StreamingPointBuffer::size() const {
	if (head == tail) {
	  return 0;
	}
	else if (head <= tail) {
	  // Buffer is contiguous
	  return tail - head;
	}
	else {
	  // Buffer wraps around
	  return (capacityLimit - head) + tail + 1;
	}
  }

} // end namespace LE

