#ifndef TEST_PIPELINE_STREAMINGPOINTBUFFER
#define TEST_PIPELINE_STREAMINGPOINTBUFFER

#include "pipeline/StreamingPointBuffer.hpp"
#include "etherdream/commands.hpp"

#include <iostream>
#include <vector>
#include <assert.h>
#include <math.h>
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

/** Take n items from the original vector and return a new vector containing them. */
shared_ptr<vector<dac_point>> dequeuePoints(shared_ptr<vector<dac_point>> original, 
	unsigned int num);
  
/** Generate a random integer. */
int randomInt(int start, int finish);

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

/** Make sure the internal ring buffer pointers chase around a few times. */
TEST(StreamingPointBufferTest, RemovedMustMatchFullCycle) {
  for (unsigned int i = 10; i < 50; i++) {
	shared_ptr<StreamingPointBuffer> buf(new StreamingPointBuffer(i));

	// Points have incremeting x, y values
	auto points = makePoints(i + MAX);

	unsigned int originalSize = points->size();
	unsigned int removedTotal = 0;
	unsigned int addedTotal = 0;

	EXPECT_EQ(points->size(), originalSize);

	// Run points through the buffer in random bursts and check for data consistency
	while (points->size() > 0 || buf->size() > 0) {
	  auto sz = buf->size();

	  int addMax = buf->capacity() - buf->size();
	  int deqMax = points->size();

	  int addNum = randomInt(0, min(addMax, deqMax));

	  if (addNum > 0) {
		auto addPoints = dequeuePoints(points, addNum);
		buf->add(addPoints);
		addedTotal += addNum;
		EXPECT_EQ(buf->size(), sz + addNum);
		EXPECT_EQ(points->size(), originalSize - addedTotal);
	  }
	  
	  sz = buf->size();

	  auto remMax = buf->size();
	  int remNum = randomInt(0, remMax);

	  if (remNum > 0) {
		auto remPoints = buf->get(remNum);
		EXPECT_EQ(remPoints->size(), remNum);
		EXPECT_EQ(buf->size(), sz - remNum);

		// XXX: Here we test for data validity!!
		for (unsigned int j = 0; j < remPoints->size(); j++) {
		  dac_point pt = remPoints->at(j);
		  EXPECT_EQ(pt.x, removedTotal);
		  EXPECT_EQ(pt.y, removedTotal);
		  removedTotal++;
		}
	  }
	}

	EXPECT_EQ(addedTotal, originalSize);
	EXPECT_EQ(removedTotal, originalSize);
	EXPECT_EQ(points->size(), 0);
	EXPECT_EQ(buf->size(), 0);
  }
}

TEST(StreamingPointBufferTest, AddRemoveAddSizeConsistency) {
  for (unsigned int i = 10; i < MAX; i++) {
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
