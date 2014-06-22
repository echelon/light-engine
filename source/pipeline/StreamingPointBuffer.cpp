#include "StreamingPointBuffer.hpp"
#include <assert.h>
#include <iostream>
#include <exception>

using namespace std;

namespace LE {

  StreamingPointBuffer::StreamingPointBuffer() : 
	allocation(DEFAULT_SIZE),
	head(0),
	tail(0)
  {
	pointBuffer.resize(DEFAULT_SIZE + 1); // Empty slot
  }

  StreamingPointBuffer::~StreamingPointBuffer() {
	// TODO
  }

  void StreamingPointBuffer::add(
	  shared_ptr<vector<dac_point>> points) 
  {
	unsigned int numAdded = points->size();
	assert(numAdded <= allocation);

	for (dac_point p: *points) {
	  pointBuffer[tail] = p; //dac_point(p);
	  tail = (tail + 1) % allocation;
	  if (tail == head) {
		// Full, overwrite
		// TODO: Make this more efficient / constant time
		head = (head + 1) % allocation;
	  }
	}
  }

  unique_ptr<vector<dac_point>> StreamingPointBuffer::get(
	  unsigned int numPoints) 
  {
	assert(numPoints <= allocation);

	vector<dac_point>* outPts = new vector<dac_point>;
	vector<dac_point>& outPtsRef = *outPts;

	outPts->reserve(numPoints);

	// Case 1 - fits into contiguous stretch
	for (unsigned int i = 0; i < numPoints; i++) {
	  unsigned int j = (head + i) % allocation;
	  outPtsRef.push_back(pointBuffer[j]);
	}

	head = (head + numPoints) % allocation;

	/*if (head + numPoints <= allocation) {
	}
	else {
	  // Case 2 - must wrap around end
	  for (unsigned int i = 0; i < numPoints; i++) {
		unsigned int j;

		outPtsRef.push_back(pointBuffer[head + i]);
	  }

	  head = (head + numPoints) % allocation;

	  cout << "TODO TODO TODO TODO 2" << endl;
	  terminate();
	}*/

	cout << "StreamBuffer.get() size is " << outPts->size() << endl;

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
	  return (allocation - tail) + head - 1;
	}
  }

} // end namespace LE

