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

	// TODO: Consider 'flattening' frame :
	// Convert 2D vec<vec<Pt>> to 1D vec<Pt>.
	// No reason to have it be 2D at this point. 
	for(; framePtsIdx < framePts.size(); framePtsIdx++) {
		Points pts = framePts[framePtsIdx];

		// FIXME FIXME FIXME I can't be this bad at C++ STL
		// TODO: Use <vector> properly. Do some math. This sucks.
		for(unsigned int j = 0; j < pts.size(); j++) {
			points.push_back(pts[j]);
			if(points.size() >= numPoints) {
				return points;
			}
		}
	}

	isInFrame = false;

	return points;
}

