#include "geo.hpp"
#include "point.hpp"

using namespace Gfx;

StaticGeo::StaticGeo() {
	// void
}

StaticGeo::StaticGeo(const Points &pts) :
	points(pts)
{
	// void
}

unsigned int StaticGeo::numPoints() {
	return points.size();
}

Points::const_iterator StaticGeo::begin() {
	return points.begin();
}

Points::const_iterator StaticGeo::end() {
	return points.end();
}
