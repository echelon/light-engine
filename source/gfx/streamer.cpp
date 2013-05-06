#include "streamer.hpp"
#include "object.hpp"

#include <iostream>

void Streamer::addObject(Object* obj)
{
	// TODO -- this is really pathetic 
	objects.push_back(obj);
}

vector<Point> Streamer::getPoints(unsigned int numPoints)
{
	vector<Point> points;
	long remaining = numPoints;

	while(remaining > 0) {
		for(unsigned int i = curObject; i < objects.size(); i++) 
		{
			vector<Point> pts;
			Object* obj = objects[i];

			curObject = i;

			pts = obj->getPoints(remaining);

			// FIXME FIXME FIXME I can't be this bad at C++ STL
			// TODO: Use <vector> properly. This sucks.
			for(unsigned int j = 0; j < pts.size(); j++) {
				points.push_back(pts[i]);
			}
			remaining -= pts.size();
		}
	}
	cout << "Streaming pts: " << points.size() << endl;

	return points;
}
