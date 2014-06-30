#ifndef TEST_PIPELINE_STREAMINGPOINTBUFFER
#define TEST_PIPELINE_STREAMINGPOINTBUFFER

#include "pipeline/StreamingPointBuffer.hpp"
#include "etherdream/commands.hpp"

#include <iostream>
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
unique_ptr<vector<dac_point>> removePoints(shared_ptr<StreamingPointBuffer> buf, 
	unsigned int numRemove);

/** Iterate to this in tests. */
const unsigned int MAX = 50;

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
  for (unsigned int i = 1; i < MAX; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));
	fillFull(buf, i);
  }
}

TEST(StreamingPointBufferTest, RemoveAll) {
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

TEST(StreamingPointBufferTest, RemovedMustMatch) {
  for (unsigned int i = 2; i < MAX; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));
	fillFull(buf, i);

	unique_ptr<vector<dac_point>> points = removePoints(buf, i);
	EXPECT_EQ(points->size(), i);
	EXPECT_TRUE(buf->isEmpty());

	for (unsigned int j = 0; j < i; j++) {
	  dac_point pt = points->at(j);
	  EXPECT_EQ(pt.x, j);
	  EXPECT_EQ(pt.y, j);
	}
  }
}

TEST(StreamingPointBufferTest, AddRemoveAddConsistency) {
  for (unsigned int i = 10; i < 11; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));
	unsigned int finalSize = 0;

	bool addMode = true;
	for (unsigned int j = i; j > 0; j--) {
	  auto sz = buf->size();

	  EXPECT_EQ(sz, finalSize);
	  if (addMode) {
		auto pts = makePoints(j);
		EXPECT_EQ(pts->size(), j);
		buf->add(pts);
		EXPECT_EQ(buf->size(), sz + j);
		finalSize += j;
	  }
	  else {
		auto pts = buf->get(j);
		EXPECT_EQ(pts->size(), j);
		EXPECT_EQ(buf->size(), sz - j);
		finalSize -= j;
	  }
	  addMode = !addMode;
	}
	EXPECT_FALSE(buf->isFull());
	EXPECT_FALSE(buf->isEmpty());
	EXPECT_EQ(buf->size(), finalSize);
  }
}

#endif
