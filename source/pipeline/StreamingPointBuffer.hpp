#ifndef LE_PIPELINE_STREAMINGPOINTBUFFER
#define LE_PIPELINE_STREAMINGPOINTBUFFER

#include "../etherdream/commands.hpp"
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

	static const unsigned int DEFAULT_SIZE = 10000;

	protected:
	  /** Storage */
	  vector<dac_point> pointBuffer;

	  /** Allocated size of the buffer */
	  unsigned int allocation;

	  /** Start of new data */
	  unsigned int head;
	  
	  /** End of new data */
	  unsigned int tail;

	public:
	  /** CTORs */
	  StreamingPointBuffer();
	  StreamingPointBuffer(unsigned int allocateSize);

	  /** DTOR. */
	  ~StreamingPointBuffer();

	  /** Add points to stream */
	  void add(const shared_ptr<vector<dac_point>>& points);

	  /** Get points from the buffer. */
	  unique_ptr<vector<dac_point>> get(unsigned int numPoints);

	  /** If buffer is depleted. */
	  bool isEmpty() const;

	  /** If buffer is full. */
	  bool isFull() const;

	  /** Get the number of items in the buffer. */
	  unsigned int size() const;
  };
}

#endif
