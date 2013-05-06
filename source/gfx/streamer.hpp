#ifndef LIGHT_ENGINE_GFX_STREAMER_HPP
#define LIGHT_ENGINE_GFX_STREAMER_HPP

#include <vector>
#include "point.hpp"

using namespace std;

class Object;

class Streamer
{

	private:
		vector<Object*> objects;

		// Current object index
		unsigned int curObject;

	public:

		Streamer(): curObject(0) {};

		/**
		 * Add an object to stream
		 * TODO: These should live outside of EtherDream code.
		 */
		void addObject(Object* obj);

		/**
		 * Return the number of points requested
		 */
		vector<Point> getPoints(unsigned int numPoints);
};

#endif
