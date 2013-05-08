#ifndef LIGHT_ENGINE_GFX_STREAMER_HPP
#define LIGHT_ENGINE_GFX_STREAMER_HPP

#include <vector>
#include "point.hpp"

using namespace std;

class Object;

class Streamer
{
	public:
		Streamer(): curObject(0), isInFrame(false) {};

		/**
		 * Add an object to stream
		 * TODO: These should live outside of EtherDream code.
		 */
		void addObject(Object* obj);

		/**
		 * Get the next numPoints points in the stream.
		 */
		Points getPoints(unsigned int numPoints);

	private:
		vector<Object*> objects;


		// Current object index
		unsigned int curObject;

		// --------- OR ----------

		// Current frame cache
		vector<Points> allObjPoints;

		// Index into frame cache
		unsigned int allObjPtsIdx;

		// If currently drawing a frame
		// False if done or not started
		bool isInFrame;

		/**
		 * Cache all the points for this frame.
		 * TODO: Rename -- doesn't adequately convey what this does!
		 */
		void cachePoints();
};

#endif
