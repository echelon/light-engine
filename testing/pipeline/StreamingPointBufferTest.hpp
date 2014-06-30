#ifndef TEST_PIPELINE_STREAMINGPOINTBUFFER
#define TEST_PIPELINE_STREAMINGPOINTBUFFER

#include "pipeline/StreamingPointBuffer.hpp"
#include "etherdream/commands.hpp"

#include <vector>
#include <assert.h>
#include <memory>
#include <gtest/gtest.h>

using namespace std;
using namespace LE;

/** Generate points */
shared_ptr<vector<dac_point>> makePoints(unsigned int number);

/** Fill, but do not overfill. */
void fillUnder(shared_ptr<StreamingPointBuffer> buf, unsigned int fillSize);

/** Fill completely. */
void fillFull(shared_ptr<StreamingPointBuffer> buf, uint fillSize);

/** Remove some points */
void removePoints(shared_ptr<StreamingPointBuffer> buf, unsigned int numRemove);

TEST(StreamingPointBufferTest, InitialState) {
  StreamingPointBuffer buf;

  EXPECT_EQ(buf.size(), 0);
  EXPECT_TRUE(buf.isEmpty());
  EXPECT_FALSE(buf.isFull());
  EXPECT_EQ(buf.capacity(), StreamingPointBuffer::DEFAULT_SIZE);

  buf = StreamingPointBuffer(100);

  EXPECT_EQ(buf.size(), 0);
  EXPECT_TRUE(buf.isEmpty());
  EXPECT_FALSE(buf.isFull());
  EXPECT_EQ(buf.capacity(), 100);
}

TEST(StreamingPointBufferTest, FillBelowCapacity) {
  const unsigned int MAX = 50;
  for (unsigned int i = 1; i < MAX; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(MAX));

	EXPECT_EQ(buf->size(), 0);
	EXPECT_TRUE(buf->isEmpty());
	EXPECT_FALSE(buf->isFull());
	EXPECT_EQ(buf->capacity(), MAX);

	fillUnder(buf, i);
  }
}

TEST(StreamingPointBufferTest, FillFull) {
  const unsigned int MAX = 50;
  for (unsigned int i = 1; i < MAX; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));
	fillFull(buf, i);
  }
}

TEST(StreamingPointBufferTest, RemoveAll) {
  const unsigned int MAX = 50;
  for (unsigned int i = 1; i < MAX; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));
	fillFull(buf, i);
	removePoints(buf, i);

	EXPECT_EQ(buf->size(), 0);
	EXPECT_TRUE(buf->isEmpty());
	EXPECT_FALSE(buf->isFull());
  }
}

TEST(StreamingPointBufferTest, RemoveSome) {
  const unsigned int MAX = 50;
  for (unsigned int i = 2; i < MAX; i++) {
	for (unsigned int j = 1; i < j; j++) {
	  shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));
	  fillFull(buf, i);
	  removePoints(buf, j);

	  EXPECT_EQ(buf->capacity(), i);
	  EXPECT_EQ(buf->size(), i - j);
	  EXPECT_FALSE(buf->isEmpty());
	  EXPECT_FALSE(buf->isFull());
	}
  }
}

#endif
