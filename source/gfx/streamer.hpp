#ifndef LIGHT_ENGINE_GFX_STREAMER_HPP
#define LIGHT_ENGINE_GFX_STREAMER_HPP

#include <vector>
#include "point.hpp"

using namespace std;

class Object;

class Streamer
{
	public:
		/**
		 * CTOR. 
		 */
		Streamer(): curObject(0), isInFrame(false) {};

		/**
		 * Add an object to be streamed
		 * TODO: Need efficient way to remove objects and
		 * change their visibility, etc.
		 */
		void addObject(Object* obj);

		/**
		 * Get the next numPoints points in the stream.
		 * 	- Hands off to other algorithms to perform tracking, etc.
		 */
		Points getPoints(unsigned int numPoints);

	private:
		// Objects in the stream
		vector<Object*> objects;

		// Frame cache 
		vector<Points> framePts;

		// Index into frame cache 
		unsigned int framePtsIdx;

		// If currently drawing a frame
		// False if done or not started
		bool isInFrame;

		/**
		 * Cache all the points for this frame, and calculate
		 * necessary tracking between objects.
		 * 	- Saved in framePts.
		 */
		void freezeFrame();
};

#endif
