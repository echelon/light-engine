#ifndef LIGHT_ENGINE_GFX_COLOR_HPP
#define LIGHT_ENGINE_GFX_COLOR_HPP

struct Color 
{
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

	Color():
			r(0.0f), g(0.0f), b(0.0f), i(0.0f),
			isBlank(false) {};

	Color(float _r, float _g, float _b) :
			r(_r), g(_g), b(_b), i(0.0f),
			isBlank(false) {
				// TODO: Set isBlank based on RGB value
			};

	Color(float _r, float _g, float _b, float _i, bool _isBlank):
			r(_r), g(_g), b(_b), i(_i),
			isBlank(_isBlank) {};
};

const Color INVISIBLE = Color(0.0f, 0.0f, 0.0f, 0.0f, true);
const Color RED   = Color(100000.0f, 0.0f, 0.0f);
const Color GREEN = Color(0.0f, 100000.0f, 0.0f);
const Color BLUE  = Color(0.0f, 0.0f, 100000.0f);
const Color WHITE = Color(100000.0f, 10000.0f, 100000.0f);

#endif
