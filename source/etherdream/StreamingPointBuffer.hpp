#ifndef LE_ETHERDREAM_STREAMINGPOINTBUFFER
#define LE_ETHERDREAM_STREAMINGPOINTBUFFER

#include "commands.hpp"
#include <vector>
#include <memory>

using namespace std;

namespace LE {
  /**
   * Stream points into an intermediate ring buffer. 
   * This is useful for buffering the points in a frame as they
   * get sent to the dac as smaller packets. 
   */
  class StreamingPointBuffer {

	public: 
	  static const unsigned int DEFAULT_SIZE;

	protected:
	  /** Storage */
	  vector<dac_point> pointBuffer;

	  /** Allocated size of the buffer (n) */
	  unsigned int capacityLimit;

	  /** Internal size of the buffer (n+1) */
	  unsigned int allocation;

	  /** Start of new data */
	  unsigned int head;
	  
	  /** End of new data */
	  unsigned int tail;

	public:
	  /** CTORs */
	  StreamingPointBuffer();
	  StreamingPointBuffer(unsigned int sizeCapacity);

	  /** DTOR. */
	  ~StreamingPointBuffer();

	  /** Add points to stream */
	  void add(shared_ptr<vector<dac_point>> points);

	  /** Get points from the buffer. */
	  unique_ptr<vector<dac_point>> get(unsigned int numPoints);

	  /** If buffer is depleted. */
	  bool isEmpty() const;

	  /** If buffer is full. */
	  bool isFull() const;

	  /** Get the number of items in the buffer. */
	  unsigned int size() const;

	  /** Get the allotted size of the buffer. */
	  unsigned int capacity() const 
		  { return capacityLimit; };
  };
}

#endif
