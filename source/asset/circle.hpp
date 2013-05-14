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
			radius(1.0f), numPoints(100) {};
			// Note: 100 points is the same as in circle.py

		Circle(float _radius):
			Object(),
			radius(_radius), numPoints(100) {};

		Circle(float _radius, int npoints):
			Object(),
			radius(_radius), numPoints(npoints) {};

		//virtual Points getPoints(unsigned int num);

		virtual Points getAllPoints();


	protected:
		// Radius <= (0.0, 1.0] 
		// TODO: enforce size
		float radius;

		// How many points comprise the circle
		unsigned int numPoints;
};

#endif
