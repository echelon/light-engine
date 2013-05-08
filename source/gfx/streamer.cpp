#include "streamer.hpp"
#include "object.hpp"

#include <iostream>

void Streamer::addObject(Object* obj)
{
	// TODO -- this is really pathetic 
	objects.push_back(obj);
}

void Streamer::cachePoints()
{
	allObjPoints.clear();
	allObjPtsIdx = 0;

	// Get all the points for the frame
	for(unsigned int i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		if(!obj->isVisible) {
			continue;
		}
		allObjPoints.push_back(obj->getAllPoints());
	}

	// TODO: Blanking should be applied here...
}

Points Streamer::getPoints(unsigned int numPoints)
{
	// No blanking or other path optimizations are performed 
	// in this algorithm. The only job here is to send points. 
	
	Points points;

	if(!isInFrame) {
		isInFrame = true;
		cachePoints();
	}

	// TODO: Consider 'flattening' frame :
	// Convert 2D vec<vec<Pt>> to 1D vec<Pt>.
	// No reason to have it be 2D at this point. 
	for(; allObjPtsIdx < allObjPoints.size(); allObjPtsIdx++) {
		Points pts = allObjPoints[i];

		// FIXME FIXME FIXME I can't be this bad at C++ STL
		// TODO: Use <vector> properly. Do some math. This sucks.
		for(unsigned int j = 0; j < pts.size(); j++) {
			points.push_back(pts[i]);
			if(points.size() >= numPoints) {
				return points;
			}
		}
	}

	isInFrame = false;

	return points;
}

