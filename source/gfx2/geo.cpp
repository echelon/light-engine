#include "geo.hpp"
#include "point.hpp"

using namespace Gfx;

StaticGeo::StaticGeo() {
	// void
}

StaticGeo::StaticGeo(const Paths &pths) :
	paths(pths)
{
	// void
}

StaticGeo::StaticGeo(const Points &pts)
{
	paths.push_back(Path(pts));
}

unsigned int StaticGeo::numPaths() const {
	return paths.size();
}

// TODO
unsigned int StaticGeo::numPoints() const
{
	unsigned int count = 0;

	for(Paths::const_iterator it = begin(); it != end(); ++it) {
		count += it->numPoints();
	}

	return count;
}


Paths::const_iterator StaticGeo::begin() const {
	return paths.begin();
}

Paths::const_iterator StaticGeo::end() const {
	return paths.end();
}
