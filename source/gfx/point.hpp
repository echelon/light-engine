#ifndef LIGHT_ENGINE_GFX_POINT_HPP
#define LIGHT_ENGINE_GFX_POINT_HPP

#include <vector>
#include "color.hpp"

struct Point 
{
	/**
	 * Coordinates 
	 *  - in range [-1, 1] ? 
	 */
	float x;
	float y;

	/**
	 * Colors
	 */
	float r;
	float g;
	float b;
	float i; // indigo/violet

	/**
	 * Blanking flag
	 * TODO: Good idea to bypass RGB?
	 */
	bool isBlank;

	Point():
			x(0.0f), y(0.0f), r(0.0f), g(0.0f), b(0.0f), i(0.0f),
			isBlank(false) {};

	Point(float _x, float _y, float _r, float _g, float _b) :
			x(_x), y(_y), r(_r), g(_g), b(_b), i(0.0f),
			isBlank(false) {
				// TODO: Set isBlank based on RGB value
			};

	Point(float _x, float _y, float _r, float _g, float _b, 
		  float _i, bool _isBlank):
			x(_x), y(_y), r(_r), g(_g), b(_b), i(_i),
			isBlank(_isBlank) {};

	Point(float _x, float _y, Color c) :
			x(_x), y(_y), 
			r(c.r), g(c.g), b(c.b), i(c.i), isBlank(c.isBlank) {};

};

typedef std::vector<Point> Points;

#endif
