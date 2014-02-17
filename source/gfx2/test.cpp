#include <cstdlib>
#include <iostream>

#include "geo.hpp"
#include "point.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	cout << "Testing gfx2" << endl;

	Gfx::StaticGeo g;

	cout << "Num Points: " << g.numPoints() << endl;

	Gfx::Points pts;

	pts.push_back(Gfx::Point(1.0f, 1.0f, 1.0f));
	pts.push_back(Gfx::Point(2.0f, 2.0f, 2.0f));
	pts.push_back(Gfx::Point(3.3f, 3.3f, 3.001111f));

	Gfx::StaticGeo g2(pts);

	cout << "Num Points: " << g2.numPoints() << endl;

	for(Gfx::Points::const_iterator it = g2.begin(); it != g2.end(); ++it) {
		//cout << "Element" << endl;
		cout << it->toString() << endl;
	}
}

