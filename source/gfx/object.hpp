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
		Object() : visible(true) {};

		/**
		 * Request numPoints for the object.
		 *  - XXX: Can return less.
		 */
		virtual Points getPoints(unsigned int numPoints) {
			cerr << "Wrong getPoints!!!" << endl;
			Points pts;
			return pts;
		};
		
		/**
		 * Request all points for the object.
		 */
		virtual Points getAllPoints() {
			cerr << "Wrong getAllPoints!!!" << endl;
			Points pts;
			return pts;
		};

		void setVisible(bool v) { visible = v; };
		bool isVisible() { return visible; };

	private:
		// If object is currently visible
		bool visible;

};

#endif
