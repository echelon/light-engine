#ifndef LIGHT_ENGINE_GFX_OBJECT_HPP
#define LIGHT_ENGINE_GFX_OBJECT_HPP

#include <vector>
#include <iostream>
#include "point.hpp"
#include "../etherdream/types.hpp"

using namespace std;

/**
 * TODO: Rename from 'object'. This term is way too loaded.
 */

class Object {

	public:
		Object() : 
			visible(true),
			blankingPtsIn(10),
			blankingPtsOut(10),
			r(CMAX),
			g(CMAX),
			b(CMAX),
			i(0) {};

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

		/**
		 * Set object visibility
		 */
		void setVisible(bool v) { visible = v; };
		bool isVisible() { return visible; };

		/**
		 * Set blanking
		 */
		void setBlankingPtsIn(unsigned int n) {
			blankingPtsIn = n;
		};

		void setBlankingPtsOut(unsigned int n) {
			blankingPtsOut = n;
		};

		unsigned int getBlankingPtsIn() { return blankingPtsIn; };
		unsigned int getBlankingPtsOut() { return blankingPtsOut; };

		void setColor(unsigned int _r, unsigned int _g, 
			unsigned int _b) {
					r = _r;
					g = _g;
					b = _b;
		};

	protected:
		// If object is currently visible
		bool visible;

		unsigned int blankingPtsIn;
		unsigned int blankingPtsOut;

		// TODO: Appropriate level to handle color?
		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int i;
};

#endif
