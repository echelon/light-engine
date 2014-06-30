#include "StreamingPointBufferTest.hpp"

shared_ptr<vector<dac_point>> makePoints(unsigned int number) {
  shared_ptr<vector<dac_point>> points(new vector<dac_point>());
  for (unsigned int i = 0; i < number; i++) {
	points->push_back(dac_point());
  }
  return points;
}

void fillUnder(shared_ptr<StreamingPointBuffer> buf, unsigned int fillSize) {
  assert(fillSize < buf->capacity());

  auto points = makePoints(fillSize);
  EXPECT_EQ(points->size(), fillSize);

  buf->add(points);

  EXPECT_EQ(buf->size(), fillSize);
  EXPECT_FALSE(buf->isFull());
  EXPECT_FALSE(buf->isEmpty());
}

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

