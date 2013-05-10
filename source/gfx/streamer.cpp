#include "streamer.hpp"
#include "object.hpp"
#include "tracking.hpp"

#include <iostream>

void Streamer::addObject(Object* obj)
{
	// TODO -- this is really pathetic 
	objects.push_back(obj);
}

void Streamer::freezeFrame()
{
	vector<Points> ppts;

	if(framePts.size() > 0 && framePts.back().size() > 0) {
		oldFramePt = framePts.back().back();
	}

	framePts.clear();
	framePtsIdx = 0;

	// Get all the points for the frame
	for(unsigned int i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		if(!obj->isVisible()) {
			continue;
		}
		ppts.push_back(obj->getAllPoints());
	}

	// Old last point tracks to new frame
	Points trk = calculate_tracking_pts(oldFramePt, ppts[0]);
	framePts.push_back(trk);

	// Add tracking between objects in current frame
	// Doesn't account for blanking between frames
	for(unsigned int i = 0; i < ppts.size() - 1; i++) {
		Points trk;
		trk= calculate_tracking_pts(ppts[i], ppts[i+1]);

		framePts.push_back(ppts[i]);
		framePts.push_back(trk);
	}
	framePts.push_back(ppts.back());
}

Points Streamer::getPoints(unsigned int numPoints)
{
	// No tracking, blanking or other path optimizations are 
	// performed in this algo. The only job here is to yield points. 
	
	Points points;

	if(!isInFrame) {
		isInFrame = true;
		freezeFrame();
	}

	// TODO/FIXME: DO tracking between last frame and current frame!

	// TODO: Consider 'flattening' frame :
	// Convert 2D vec<vec<Pt>> to 1D vec<Pt>.
	// No reason to have it be 2D at this point. 
	for(; framePtsIdx < framePts.size(); framePtsIdx++) {
		Points pts = framePts[framePtsIdx];

		// FIXME FIXME FIXME I can't be this bad at C++ STL
		// TODO: Use <vector> properly. Do some math. This sucks.
		for(;framePtsObjIdx < pts.size(); framePtsObjIdx++) {
			points.push_back(pts[framePtsObjIdx]);
			if(points.size() >= numPoints) {
				return points;
			}
		}

		framePtsObjIdx = 0;
	}

	isInFrame = false;

	return points;
}

Points Streamer::getPoints2(int numPoints)
{
	Points points;
	int required = numPoints;

	while(required >= 0) {
		Points pts = getPoints(required);
		required -= pts.size();

		// FIXME FIXME TODO: Terrible code
		for(unsigned int i = 0; i < pts.size(); i++) {
			points.push_back(pts[i]);
		}
	}

	return points;
}

