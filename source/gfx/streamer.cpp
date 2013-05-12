#include "streamer.hpp"
#include "object.hpp"
#include "tracking.hpp"
#include "color.hpp"

#include <iostream>
#include <iterator>

void Streamer::addObject(Object* obj)
{
	// TODO -- this is really pathetic 
	objects.push_back(obj);
}

void Streamer::freezeFrame()
{
	vector<Points> ppts;
	vector<Points> trks;

	unsigned int sz;

	if(frameStream.size() > 0) {
		oldFramePt = frameStream.back();
	}

	// TODO: Don't thrash memory by clear/reallocing. 
	// Use buffer more intelligently
	frameStream.clear();

	// Get all the points for the frame
	for(unsigned int i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		if(!obj->isVisible()) {
			continue;
		}
		ppts.push_back(obj->getAllPoints());
		sz += ppts.back().size();
	}

	// Old last point tracks to new frame
	Points trk = calculate_tracking_pts(oldFramePt, ppts[0], 7,
			RED);
	trks.push_back(trk);
	sz += trk.size();

	// Add tracking between objects in current frame
	// Doesn't account for blanking between frames
	for(unsigned int i = 0; i < ppts.size() - 1; i++) {
		Color c;
		switch(i%3) {
			case 0:
				c = RED;
				break;
			case 1:
				c = GREEN;
				break;
			case 2:
				c = BLUE;
				break;
			default:
				c = WHITE;
				break;
		}
		Points t = calculate_tracking_pts(ppts[i], ppts[i+1], 
				7, c);
		trks.push_back(t);
		sz += t.size();
	}

	//sz += ppts.back().size();

	// TODO: Make this efficient!!
	//frameStream.reserve(sz);

	for(unsigned int i = 0; i < ppts.size(); i++) {
		frameStream.insert(frameStream.end(), 
							trks[i].begin(), trks[i].end());

		frameStream.insert(frameStream.end(), 
							ppts[i].begin(), ppts[i].end());
	}

	frameStreamIdx = 0;
	frameStreamIt = frameStream.begin();

	cout << "Frame Size: " << frameStream.size() << endl;
}

Points Streamer::getPoints(unsigned int numPoints)
{
	// No tracking, blanking or other path optimizations are 
	// performed in this algo. The only job here is to yield points. 
	
	Points points;

	//cout << "\tgetPoints(" << numPoints << "), ";

	if(!isInFrame) {
		isInFrame = true;
		freezeFrame();
	}

	points.reserve(numPoints);

	// FIXME/TODO: Use resize, reserve, etc.
	// FIXME/TODO: If more points than exist are requested,
	// then we need to run algo again!
	for(; frameStreamIdx < frameStream.size(); frameStreamIdx++) {
		points.push_back(frameStream[frameStreamIdx]);
		if(points.size() >= numPoints) {
			++frameStreamIdx;
			//cout << "retA: " << points.size() << endl;
			return points;
		}
	}

	isInFrame = false;

	//cout << "retB: " << points.size() << endl;
	return points;
}

Points Streamer::getPoints2(int numPoints)
{
	Points points;
	int required = numPoints;

	//cout << "getPointsTwo(" << numPoints << ")";
	//cout << " @ " << frameStreamIdx << endl;

	while(required > 0) {
		Points pts = getPoints(required);
		required -= pts.size();

		// FIXME FIXME TODO: Terrible code
		for(unsigned int i = 0; i < pts.size(); i++) {
			points.push_back(pts[i]);
		}
	}

	//cout << "<-- Returning: " << points.size() << endl << endl;

	return points;
}

