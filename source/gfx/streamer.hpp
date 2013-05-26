#ifndef LIGHT_ENGINE_GFX_STREAMER_HPP
#define LIGHT_ENGINE_GFX_STREAMER_HPP

#include <vector>
#include "point.hpp"
#include "surface.hpp"

using namespace std;

class Object;

// 1250 pts/frame is equivalent to 24 fps @ 30kpps
const unsigned int DEFAULT_POINTS_PER_SEND = 1250;
const unsigned int MAX_POINTS_PER_SEND = 15000; // XXX: No basis 

class Streamer
{
	public:
		/**
		 * CTOR. 
		 */
		Streamer(): 
			isInFrame(false),
			frameStreamIdx(0),
			recommendedSendRate(DEFAULT_POINTS_PER_SEND) 
			{};

		/**
		 * Add an object to be streamed
		 * TODO: Need efficient way to remove objects and
		 * change their visibility, etc.
		 */
		void addObject(Object* obj);

		/**
		 * Change the dimensions of the projection surface.
		 */
		void setSurface(Surface s) { surface = s; };
		Surface getSurface() { return surface; };

		/**
		 * Get the next numPoints points in the stream.
		 * 	- Hands off to other algorithms to perform tracking, etc.
		 */
		Points getPoints(unsigned int numPoints);

		// Absolutely returns numPoints
		Points getPoints2(int numPoints);

		// Recommended rate heuristic 
		// FIXME/TODO/URGENT: Need to research if this works...
		// TODO/TODO/TODO: 
		// This should be an equation based on frame size, 
		// complexity, and object distances! This will need to be
		// sophisticated. DAC itself will then adjust this based on 
		// its own experience--history of reconnects, send rates,
		// buffer use, etc.
		unsigned int getRecommendedSendRate() {
			return recommendedSendRate;
		}

	private:
		// Objects in the stream
		vector<Object*> objects;

		// Frame cache 

		// Last frame last point
		Point oldFramePt;

		// Index into frame cache 
		//unsigned int framePtsIdx;

		// Index into frame cache object
		//unsigned int framePtsObjIdx;

		// If currently drawing a frame
		// False if done or not started
		bool isInFrame;

		// Flattened stream
		Points frameStream;
		Points::iterator frameStreamIt;
		unsigned int frameStreamIdx; // TODO: iterator

		// Recommended rate heuristic 
		unsigned int recommendedSendRate;

		// Projection surface
		Surface surface;

		/**
		 * Cache all the points for this frame, and calculate
		 * necessary tracking between objects.
		 * 	- Saved in framePts.
		 */
		void freezeFrame();

		/**
		 * Set recommended send rate, which DAC can choose to 
		 * obey. Don't allow to drop below 24fps heuristic.
		 * FIXME/TODO/URGENT: Need to research if this works.
		 */
		void setRecommendedSendRate(unsigned int rate) {
			if(rate < DEFAULT_POINTS_PER_SEND) {
				//recommendedSendRate = DEFAULT_POINTS_PER_SEND;
				recommendedSendRate = rate;
			}
			else if(rate > MAX_POINTS_PER_SEND) {
				recommendedSendRate = MAX_POINTS_PER_SEND;
			}
			else {
				recommendedSendRate = rate;
			}
		};
};

#endif
