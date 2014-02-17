#include <cstdlib>
#include <iostream>

#include "geo.hpp"
#include "point.hpp"
#include "path.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	cout << "Testing gfx2" << endl;

	cout << "PATH 1" << endl;
	Gfx::Path p1;

	cout << "Num Points in path: " << p1.numPoints() << endl;

	Gfx::Points pts;

	pts.push_back(Gfx::Point(1.0f, 1.0f, 1.0f));
	pts.push_back(Gfx::Point(2.0f, 2.0f, 2.0f));
	pts.push_back(Gfx::Point(3.3f, 3.3f, 3.001111f));

	cout << "PATH 2" << endl;

	Gfx::Path p2(pts);

	cout << "Num Points in path: " << p2.numPoints() << endl;

	for(Gfx::Points::const_iterator it = p2.begin(); it != p2.end(); ++it) {
		cout << it->toString() << endl;
	}

	pts.clear();

	pts.push_back(Gfx::Point(0.0f, 0.0f, 0.0f));
	pts.push_back(Gfx::Point(1.0f, 0.0f, 0.0f));
	pts.push_back(Gfx::Point(0.0f, 1.0f, 0.0f));
	pts.push_back(Gfx::Point(0.0f, 0.0f, 1.0f));

	cout << "PATH 3" << endl;

	Gfx::Path p3(pts);

	cout << "Num Points in path: " << p3.numPoints() << endl;

	// Thank you, C++11!
	for(auto it = p3.begin(); it != p3.end(); ++it) {
		cout << it->toString() << endl;
	}

	// Perhaps an iterator wrapper that calculates the velocity 
	// required to move from one point to the next.
	//
	//
	//
	
	cout << "Geo 1" << endl;

	Gfx::StaticGeo g1;

	cout << "Num Paths in geo: " << g1.numPaths() << endl;

	
	Gfx::Paths pths;

	pths.push_back(p2);
	pths.push_back(p3);
	pths.push_back(p2);

	cout << "Geo 2" << endl;

	Gfx::StaticGeo g2(pths);

	cout << "Num Paths in geo: " << g2.numPaths() << endl;
	cout << "Num Points in geo: " << g2.numPoints() << endl;

	cout << "Geo 3" << endl;

	Gfx::StaticGeo g3(pts);

	cout << "Num Paths in geo: " << g3.numPaths() << endl;
	cout << "Num Points in geo: " << g3.numPoints() << endl;

}

