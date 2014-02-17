#include "path.hpp"

using namespace Gfx;

Path::Path() {
	// void
}

Path::Path(const Points& pts) :
	points(pts)
{
	// void
}

unsigned int Path::numPoints() const {
	return points.size();
}

Points::const_iterator Path::begin() const {
	return points.begin();
}

Points::const_iterator Path::end() const {
	return points.end();
}
