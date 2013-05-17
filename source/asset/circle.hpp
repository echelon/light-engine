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
			numPoints(100) {};
			// Note: 100 points is the same as in circle.py

		Circle(float _scale):
			Object(),
			numPoints(100) {
				setScale(_scale);
			};

		Circle(float _scale, int nPoints):
			Object(),
			numPoints(nPoints) {
				setScale(_scale);
			};

		//virtual Points getPoints(unsigned int num);

		virtual Points getAllPoints() const;


	protected:
		// How many points comprise the circle
		unsigned int numPoints;
};

#endif
