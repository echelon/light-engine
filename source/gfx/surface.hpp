#ifndef LIGHT_ENGINE_GFX_SURFACE_HPP
#define LIGHT_ENGINE_GFX_SURFACE_HPP

/**
 * Defines the remapping to physical surface.
 * TODO: This simply scales the projection surface, in the future
 * I need to change the field of view so objects can go "offscreen"
 * TODO: Rename this class? We're not drawing to a surface...
 */

//class Streamer;

// FIXME: These are wrong
#define HW_X_MAXIMA 30000
#define HW_X_MINIMA -30000
#define HW_Y_MAXIMA 30000
#define HW_Y_MINIMA -30000

#include <iostream>
using namespace std;

#include "point.hpp"
class Object;

class Surface {
	//friend class Streamer;
	friend Points get_transformed_points(Object& obj, 
										 Surface surface);

	public:
		Surface():
			xMax(HW_X_MAXIMA),
			xMin(HW_X_MINIMA),
			yMax(HW_Y_MAXIMA),
			yMin(HW_Y_MINIMA)
			{ recalculate(); };
		Surface(unsigned int xMag, unsigned int yMag):
			xMax(xMag),
			xMin(-xMag),
			yMax(yMag),
			yMin(-yMag) 
			{ recalculate(); };
		Surface(int _xMax, int _yMax, int _xMin, int _yMin):
			xMax(_xMax),
			xMin(_xMin),
			yMax(_yMax),
			yMin(_yMin) 
			{ recalculate(); };

		void setX(int _xMax, int _xMin) {
			xMax = _xMax;
			xMin = _xMin;
			recalculate();
		};

		void setY(int _yMax, int _yMin) {
			yMax = _yMax;
			yMin = _yMin;
			recalculate();
		};

		void setMaxX(int n) { xMax = n; recalculate(); };
		void setMinX(int n) { xMin = n; recalculate(); };
		void setMaxY(int n) { yMax = n; recalculate(); };
		void setMinY(int n) { yMin = n; recalculate(); };

		int getMaxX() { return xMax; };
		int getMinX() { return xMin; };
		int getMaxY() { return yMax; };
		int getMinY() { return yMin; };

		void setMagX(unsigned int n) {
			xMax = n;
			xMin = -n;
			recalculate();
		};

		void setMagY(unsigned int n) {
			yMax = n;
			yMin = -n;
			recalculate();
		};
	
	private:
		// Cached range
		int xMax;
		int xMin;
		int yMax;
		int yMin;

		// Used to transform to new range
		int xScale;
		int xShift;
		int yScale;
		int yShift;

		/**
		 * Calculate the scale and shift.
		 * Given an arbitrary range as [A, B],
		 *  - length = [B - A]
		 * 	- scale = [lenNewRange/lenOrigRange]
		 *  - shift = B - scale OR A + scale
		 */
		void recalculate() {
			// unit scale is [-1, 1]
			// length of unit scale is thus 2
			xScale = (xMax - xMin) / 2; 
			yScale = (yMax - yMin) / 2; 
			xShift = xMin + xScale;	
			yShift = yMin + yScale;	
		}
};

#endif
