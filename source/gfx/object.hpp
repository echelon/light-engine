#ifndef LIGHT_ENGINE_GFX_OBJECT_HPP
#define LIGHT_ENGINE_GFX_OBJECT_HPP

#include <vector>
#include <iostream>
#include "point.hpp"
#include "position.hpp"
#include "color.hpp"
#include "../etherdream/types.hpp"

using namespace std;

/**
 * TODO: Rename from 'object'. This term is way too loaded.
 */

class Object {

	public:
		Object() : 
			visible(true),
			scale(0.25),
			blankingPtsIn(10),
			blankingPtsOut(10),
			color(WHITE),
			pos()
			{};

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
		virtual Points getAllPoints() const {
			cerr << "Wrong getAllPoints!!!" << endl;
			Points pts;
			return pts;
		};

		/**
		 * Object visibility
		 */
		void setVisible(bool v) { visible = v; };
		bool isVisible() { return visible; };

		/**
		 * Object scaling 
		 */
		float getScale() const { return scale; };
		void setScale(float s) { scale = s; };

		/**
		 * Object positioning
		 */
		Position getPosition() const { return pos; };
		void setPosition(const Position p) { pos = p; };
		void setPosition(int x, int y) { 
			pos.x = x;
			pos.y = y;
		};
		void setPositionX(int x) { pos.x = x; };
		void setPositionY(int y) { pos.y = y; };

		/**
		 * Set blanking
		 * TODO: Not yet implemented anywhere
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
					color.r = _r;
					color.g = _g;
					color.b = _b;
		};

		void setColor(Color c) { color = c; };

	protected:
		// If object is currently visible
		bool visible;

		// Object scale in [0.0, 1.0]
		float scale;

		unsigned int blankingPtsIn;
		unsigned int blankingPtsOut;

		// TODO: Appropriate level to handle color?
		Color color;

		// TODO: Not formal reference frame yet
		Position pos;
};

#endif
