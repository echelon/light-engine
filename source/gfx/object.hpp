#ifndef LIGHT_ENGINE_GFX_OBJECT_HPP
#define LIGHT_ENGINE_GFX_OBJECT_HPP

#include <vector>
#include <iostream>
#include "point.hpp"
#include "position.hpp"
#include "color.hpp"
#include "../etherdream/types.hpp"

class Illuminator;

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
			pos(),
			color(WHITE),
			illuminator(0)
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
		 * Object static color
		 */
		void setColor(Color c) { color = c; };
		void setColor(float r, float g, float b) {
			color.r = r;
			color.g = g;
			color.b = b;
		};

		/**
		 * Object illuminator 
		 * 	-- dynamic lighting system
		 * 	TODO/FIXME: POINTER OWNERSHIP!!
		 */
		bool hasIlluminator() const { return illuminator == 0; };

		void setIlluminator(Illuminator* illum) {
			illuminator = illum;
		};

		Illuminator* getIlluminator() { return illuminator; };


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

	protected:
		// If object is currently visible
		bool visible;

		// Object scale in [0.0, 1.0]
		float scale;

		unsigned int blankingPtsIn;
		unsigned int blankingPtsOut;

		// TODO: Not formal reference frame yet
		Position pos;

		// TODO: Appropriate level to handle color?
		Color color;

		// Illuminator object
		Illuminator* illuminator;
		//bool hasIlluminator;
};

#endif
