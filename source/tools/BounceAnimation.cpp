#include "BounceAnimation.hpp"
#include <thread>
#include <chrono>
#include <assert.h>
#include <iostream>

namespace LE {

const float BounceAnimation::DEFAULT_BOUNDARY_TOP = 10000.0f;
const float BounceAnimation::DEFAULT_BOUNDARY_RIGHT = -10000.0f;
const float BounceAnimation::DEFAULT_BOUNDARY_BOTTOM = -10000.0f;
const float BounceAnimation::DEFAULT_BOUNDARY_LEFT = 10000.0f;

const float BounceAnimation::DEFAULT_MAX_VELOCITY_MAGNITUDE = 100.0f;
const float BounceAnimation::DEFAULT_MIN_VELOCITY_MAGNITUDE = 50.0f;

BounceAnimation::BounceAnimation(unsigned int numPositions) :
  positions(numPositions, Position()),
  velocities(numPositions, Position()),
  boundaryTop(DEFAULT_BOUNDARY_TOP),
  boundaryRight(DEFAULT_BOUNDARY_RIGHT),
  boundaryBottom(DEFAULT_BOUNDARY_BOTTOM),
  boundaryLeft(DEFAULT_BOUNDARY_LEFT),
  minVelocityMagnitude(DEFAULT_MIN_VELOCITY_MAGNITUDE),
  maxVelocityMagnitude(DEFAULT_MAX_VELOCITY_MAGNITUDE),
  random(),
  // Technically, distributions are over [A, B) / not inclusive.
  horizontal(boundaryLeft, boundaryRight),
  vertical(boundaryBottom, boundaryTop),
  magnitude(minVelocityMagnitude, maxVelocityMagnitude),
  sign(0.5),
  sleepMilliseconds(5),
  threadRunning(false),
  thread()
{
  assert(minVelocityMagnitude > 0.0f);
  assert(maxVelocityMagnitude > 0.0f);

  randomizeVelocities();
}

BounceAnimation::~BounceAnimation() {
}

void BounceAnimation::randomizePositions() {
  mutex.lock();
  for (auto & pos : positions) {
	pos.x = horizontal(random);
	pos.y = vertical(random);
  }
  mutex.unlock();
}

void BounceAnimation::randomizeVelocities() {
  mutex.lock();
  for (auto & vel : velocities) {
	vel.x = magnitude(random) * (sign(random) ? 1 : -1);
	vel.y = magnitude(random) * (sign(random) ? 1 : -1);
  }
  mutex.unlock();
}

void BounceAnimation::setBoundaries(float top_, float right, 
	float bottom, float left) {
  assert(top_ > bottom);
  assert(left > right);
  mutex.lock();
  boundaryTop = top_;
  boundaryRight = right;
  boundaryRight = bottom;
  boundaryRight = left;
  mutex.unlock();
}

void BounceAnimation::setVelocityMagnitudes(float min_, float max_) {
  assert(min_ < max_);
  mutex.lock();
  minVelocityMagnitude = min_;
  maxVelocityMagnitude = max_;
  mutex.unlock();
}

unique_ptr<vector<Position>> BounceAnimation::getPositionsUnique() const {
  mutex.lock();
  vector<Position>* copied = 
	new vector<Position>(positions.begin(), positions.end());
  mutex.unlock();
  return unique_ptr<vector<Position>>(copied);
}

shared_ptr<vector<Position>> BounceAnimation::getPositionsShared() const {
  mutex.lock();
  vector<Position>* copied = 
	new vector<Position>(positions.begin(), positions.end());
  mutex.unlock();
  return shared_ptr<vector<Position>>(copied);
}

bool BounceAnimation::start() {
  mutex.lock();
  if (threadRunning) {
	mutex.unlock();
	return false;
  }
  threadRunning = true;
  mutex.unlock();
  thread = std::thread(&BounceAnimation::animationThread, this);
  return true;
}

void BounceAnimation::animationThread() {
  while (true) {
	mutex.lock();
	for (unsigned int i = 0; i < positions.size(); i++) {
	  Position velocity = velocities[i];
	  Position position = positions[i];

	  position.x += velocity.x;
	  position.y += velocity.y;

	  if (position.x >= boundaryLeft) {
		position.x = boundaryLeft;
		velocity.x = magnitude(random) * -1;
	  }
	  else if (position.x <= boundaryRight) {
		position.x = boundaryRight;
		velocity.x = magnitude(random);
	  }

	  if (position.y >= boundaryTop) {
		position.y = boundaryTop;
		velocity.y = magnitude(random) * -1;
	  }
	  else if (position.y <= boundaryBottom) {
		position.y = boundaryBottom;
		velocity.y = magnitude(random);
	  }
	  
	  velocities[i] = velocity;
	  positions[i] = position;
	}

	mutex.unlock();

	// Sleep so not CPU-bound
	this_thread::sleep_for(chrono::milliseconds(sleepMilliseconds));
  }
}

} // end namespace
