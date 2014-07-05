#include "StreamingPointBufferTest.hpp"

#include <random>

shared_ptr<vector<dac_point>> makePoints(unsigned int number) {
  shared_ptr<vector<dac_point>> points(new vector<dac_point>());
  for (unsigned int i = 0; i < number; i++) {
	points->push_back(dac_point(i, i));
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
	points->push_back(dac_point(i, i));
  }

  EXPECT_EQ(fillSize, points->size());

  buf->add(points);

  EXPECT_EQ(fillSize, buf->size());
  EXPECT_TRUE(buf->isFull());
  EXPECT_FALSE(buf->isEmpty());
}

unique_ptr<vector<dac_point>> removePoints(shared_ptr<StreamingPointBuffer> buf, 
	unsigned int numRemove) {
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

  return pts;
}

shared_ptr<vector<dac_point>> dequeuePoints(shared_ptr<vector<dac_point>> original, 
	unsigned int num) {
  assert(num > 0);
  assert(num <= original->size());

  auto start = original->begin();
  auto finish = original->begin() + num;

  shared_ptr<vector<dac_point>> points(new vector<dac_point>(start, finish));
  original->erase(start, finish);

  return points;
}

int randomInt(int start, int finish) {
  random_device rd;
  mt19937 randgen(rd());
  return uniform_int_distribution<>(start, finish)(randgen);
}

