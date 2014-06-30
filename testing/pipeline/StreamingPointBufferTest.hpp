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

shared_ptr<vector<dac_point>> makePoints(unsigned int number);

void fillUnder(shared_ptr<StreamingPointBuffer> buf, unsigned int fillSize);
void fillFull(shared_ptr<StreamingPointBuffer> buf, uint fillSize);
void fillOver(shared_ptr<StreamingPointBuffer> buf, uint fillSize);
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

/** Generate points */
shared_ptr<vector<dac_point>> makePoints(unsigned int number) {
  shared_ptr<vector<dac_point>> points(new vector<dac_point>());
  for (unsigned int i = 0; i < number; i++) {
	points->push_back(dac_point());
  }
  return points;
}

/** Fill, but do not overfill. */
void fillUnder(shared_ptr<StreamingPointBuffer> buf, unsigned int fillSize) {
  assert(fillSize < buf->capacity());

  auto points = makePoints(fillSize);
  EXPECT_EQ(points->size(), fillSize);

  buf->add(points);

  EXPECT_EQ(buf->size(), fillSize);
  EXPECT_FALSE(buf->isFull());
  EXPECT_FALSE(buf->isEmpty());
}

/** Fill completely. */
void fillFull(shared_ptr<StreamingPointBuffer> buf, unsigned int fillSize) {
  assert(fillSize == buf->capacity());

  shared_ptr<vector<dac_point>> points(new vector<dac_point>());
  for (unsigned int i = 0; i < fillSize; i++) {
	points->push_back(dac_point());
  }

  EXPECT_EQ(fillSize, points->size());

  buf->add(points);

  EXPECT_EQ(fillSize, buf->size());
  EXPECT_TRUE(buf->isFull());
  EXPECT_FALSE(buf->isEmpty());
}

/** Remove some points */
void removePoints(shared_ptr<StreamingPointBuffer> buf, unsigned int numRemove) {
  assert(numRemove > 0);
  assert(numRemove <= buf->capacity());

  unsigned int startSize = buf->size();
  unsigned int maxSize = buf->capacity();

  unique_ptr<vector<dac_point>> pts = buf->get(numRemove);
  EXPECT_EQ(pts->size(), numRemove);

  EXPECT_EQ(buf->size(), startSize - numRemove);
  EXPECT_TRUE(buf->size() >= 0);
  EXPECT_TRUE(buf->size() < maxSize);
  EXPECT_FALSE(buf->isFull());
}

#endif
