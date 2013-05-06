#ifndef LIGHT_ENGINE_ASSET_CIRCLE_HPP
#define LIGHT_ENGINE_ASSET_CIRCLE_HPP

#include <vector>
#include "../gfx/point.hpp"
#include "../gfx/object.hpp"

using namespace std;

class Circle : public Object 
{
	public:
		Circle(): 
			Object(),
			radius(1.0f), numPoints(1000), position(0) {};

		Circle(float _radius):
			Object(),
			radius(_radius), numPoints(1000), position(0) {};

		virtual vector<Point> getPoints(unsigned int num);

	private:
		// Radius <= (0.0, 1.0] 
		// TODO: enforce size
		float radius;

		// How many points comprise the circle
		unsigned int numPoints;

		// Current stream draw position/index
		unsigned int position; 
};

#endif
