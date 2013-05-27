#ifndef LIGHT_ENGINE_GFX_OBJECT_HPP
#define LIGHT_ENGINE_GFX_OBJECT_HPP

#include <memory>
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
		/**
		 * CTOR
		 * Sets sensible defaults and generates static points (if any)
		 */
		Object() : 
			visible(true),
			scale(0.25),
			blankingPtsIn(10),
			blankingPtsOut(10),
			pos(),
			color(WHITE),
			illuminator(0) {
				// Empty CTOR 
			};
		
		/**
		 * Request all points for the object.
		 *  - Returns static points by default, but can be overridden
		 */
		virtual const Points* getPoints() { 
			if(!staticPoints) {
				generateStaticPoints();
			}
			return staticPoints.get();
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
		Illuminator* getIlluminator() { return illuminator; };
		void setIlluminator(Illuminator* illum) {
			illuminator = illum;
		};

		/**
		 * Set blanking
		 * TODO: Not yet implemented anywhere
		 */
		void setBlankingPtsIn(unsigned int n) { blankingPtsIn = n;};
		void setBlankingPtsOut(unsigned int n) { blankingPtsOut = n;};
		unsigned int getBlankingPtsIn() { return blankingPtsIn; };
		unsigned int getBlankingPtsOut() { return blankingPtsOut; };

	protected:
		// If object is currently visible
		// If false, do not draw
		bool visible;

		// Object scale in [0.0, 1.0]
		float scale;

		unsigned int blankingPtsIn;
		unsigned int blankingPtsOut;

		// TODO: Not formal reference frame yet
		Position pos;

		/**
		 * Object color.
		 *  - Color is a single, static color
		 *  - Illuminator is a color generator. If set, it will be
		 *    used instead of Color.
		 */
		Color color;
		Illuminator* illuminator;

		// Cached points generated at object creation
		//Points* staticPoints;
		unique_ptr<Points> staticPoints;

		/**
		 * OVERRIDE THIS
		 * Generate the points of the object.
		 * Unless getAllPoints() is overridden by a possibly-dynamic
		 * method, static points that are generated by this method,
		 * which is called at object creation, will be returned. 
		 */
		virtual void generateStaticPoints() {
			cout << "[!] Default generateStaticPoints called." << endl;
			staticPoints = unique_ptr<Points>(new Points());
		};
};

#endif
