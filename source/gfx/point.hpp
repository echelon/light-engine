#ifndef LIGHT_ENGINE_GFX_POINT_HPP
#define LIGHT_ENGINE_GFX_POINT_HPP

#include <vector>
#include "color.hpp"
#include "position.hpp"

struct Point 
{
	/**
	 * Coordinates 
	 */
	Position pos;

	/**
	 * Colors
	 */
	Color color;

	Point():
		pos(), 
		color() 
		{};

	Point(float _x, float _y, float _r, float _g, float _b) :
		pos(_x, _y),
		color(_r, _g, _b)
		{};

	Point(float _x, float _y, const Color& c) :
		pos(_x, _y),
		color(c)
		{};

	Point(const Position& p, const Color& c) :
		pos(p),
		color(c)
		{};
	
	Point(const Point& p):
		pos(p.pos),
		color(p.color)
		{}
};

typedef std::vector<Point> Points;

#endif
