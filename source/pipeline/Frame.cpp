#include "Frame.hpp"
#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>    // std::move (ranges)
#include <utility>      // std::move (objects)

using namespace std;

namespace LE {

  int Frame::CREATE_COUNTER = 0;

  Frame::Frame() :
	frameMode(SWAP),
	drawingState(DRAWING_STATE_UNINITIALIZED),
	frameId(CREATE_COUNTER++),
	numberBeginDrawCalls(0),
	numberDrawCalls(0),
	numberFinishCalls(0),
	numberGetPointsCalls(0),
	numberGotPointsCalls(0),
	countToModeSwap(0),
	countToModeLasing(0),
	countToModeDrawing(0),
	points()
  {
	cout << points.size() << endl;
  }

  Frame::~Frame() {
  }

  unsigned int Frame::getNumberPoints() const {
	return points.size();
  }

  void Frame::beginDrawing() {
	assert(drawingState == DRAWING_STATE_DRAWING_READY);
	numberBeginDrawCalls++;
	drawingState = DRAWING_STATE_DRAWING_NOW;
	points.resize(0); // Doesn't change space allocation!
  }

  void Frame::draw(const Geometry& geo) {
	assert(drawingState == DRAWING_STATE_DRAWING_NOW);
	points.insert(points.begin(), geo.points.begin(), geo.points.end());
	numberDrawCalls++;
  }

  void Frame::draw(const Geometry& geo, const MatrixStack& matStack) {
	// TODO
  }

  void Frame::finishDrawing() {
	assert(drawingState == DRAWING_STATE_DRAWING_NOW);
	numberFinishCalls++;
	drawingState = DRAWING_STATE_DRAWING_FINISHED;
  }

  void Frame::setFrameMode(FrameMode toMode) {
	// Assert that our state is in order
	switch (toMode) {
	  case SWAP:
		assert(frameMode != SWAP);
		if (frameMode == DRAWING) {
		  assert(drawingState == DRAWING_STATE_DRAWING_FINISHED);
		}
		countToModeSwap++;
		break;

	  case DRAWING:
		assert(frameMode == SWAP);
		drawingState = DRAWING_STATE_DRAWING_READY;
		countToModeDrawing++;
		break;

	  case LASING:
		assert(frameMode == SWAP);
		countToModeLasing++;
		break;
	}
	frameMode = toMode;
  }

  void Frame::markGetPoints() {
	numberGetPointsCalls++;
  }

  void Frame::markGotPoints() {
	numberGotPointsCalls++;
  }

  // XXX: Doesn't automatically numberGetPointsCalls++
  Points Frame::copyPoints() const {
	vector<Point> pointCopy(points.begin(), points.end());
	pointCopy.reserve(points.size());
	return move(pointCopy); // TODO
  }

  void Frame::printStats() const {
	string modeStr;
	string drawStr;

	switch (frameMode) {
	  case DRAWING: 
		modeStr = "DRAW";
		break;
	  case LASING:
		modeStr = "LASE";
		break;
	  case SWAP:
		modeStr = "SWAP";
		break;
	}

	switch (drawingState) {
	  case DRAWING_STATE_UNINITIALIZED: 
		drawStr = "NOT_YET_INIT";
		break;
	  case DRAWING_STATE_WRONG_MODE: 
		drawStr = "WRONG_MODES";
		break;
	  case DRAWING_STATE_DRAWING_READY:
		drawStr = "BEFORE_DRAW";
		break;
	  case DRAWING_STATE_DRAWING_NOW:
		drawStr = "DRAWING_NOW";
		break;
	  case DRAWING_STATE_DRAWING_FINISHED:
		drawStr = "DRAWING_END";
		break;
	}

	cout << "Frame #" << frameId << " "
	  << " mode: " << modeStr
	  << " drawstate: " << drawingState 
	  << " #toDraw: " << countToModeDrawing
	  << " #toLase: " << countToModeLasing
	  << " #toSwap: " << countToModeSwap
	  << " ("
	  << numberBeginDrawCalls << " begin "
	  << numberDrawCalls << " draw "
	  << numberFinishCalls << " end) vs ("
	  << numberGetPointsCalls << " get "
	  << numberGotPointsCalls << " got)"
	  << endl;
  }

} // end namespace LE

