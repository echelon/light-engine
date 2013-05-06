#ifndef LIGHT_ENGINE_GFX_OBJECT_HPP
#define LIGHT_ENGINE_GFX_OBJECT_HPP

#include <vector>
#include <iostream>
#include "point.hpp"

using namespace std;

/**
 * TODO: Rename from 'object'. This term is way too loaded.
 */

class Object {

	public:
		Object() {};

		/**
		 * Request numPoints for the object.
		 *  - Can return less.
		 *  FIXME: Should be virtual interface only
		 */
		virtual vector<Point> getPoints(unsigned int numPoints) {
			cerr << "Wrong getPoints!!!" << endl;
			vector<Point> pts;
			return pts;
		};
};

#endif
