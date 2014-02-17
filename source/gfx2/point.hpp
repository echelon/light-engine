#ifndef LIGHT_ENGINE_GFX2_POINT_HPP
#define LIGHT_ENGINE_GFX2_POINT_HPP

// TODO: header files shouldn't include STL
#include <vector>
#include <string>
#include <sstream>

namespace Gfx {

	/**
	 * Three-dimensional points.
	 *
	 * Points are in 3D space for the following reasons:
	 *		- Easier matrix math
	 *		- Transformations on multiple axes (see previous)
	 *		- Geometry such as an abstract / abstract generator requires this
	 *		- Not wasting RAM
	 *		- Can easily do flat geometry with z=1.0
	 */
	struct Point
	{
		float x;
		float y;
		float z;

		Point(): x(0.0f), y(0.0f), z(0.0f) {};
		Point(float x_, float y_): x(x_), y(y_), z(1.0f) {};
		Point(float x_, float y_, float z_): x(x_), y(y_), z(z_) {};
		Point(const Point& p): x(p.x), y(p.y), z(p.z) {};

		const Point operator+(const Point& p) const {
			return Point(
				x + p.x,
				y + p.y,
				z + p.z
			);
		};

		const Point operator-(const Point& p) const {
			return Point(
				x - p.x,
				y - p.y,
				z - p.z
			);
		};

		// TODO: What other operators / math operations should be supported?
		
		std::string toString() const {
			std::stringstream ss;
			ss.precision(2);
			ss << "<" << x << "," << y << "," << z << ">";
			return ss.str();
		};
	};

	// TODO: Good typedef?
	typedef std::vector<Point> Points;

} // end namespace Gfx


#endif
