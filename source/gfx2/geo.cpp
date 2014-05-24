#include "geo.hpp"
#include "point.hpp"

using namespace Gfx;

Geo::Geo() {
	// void
}

Geo::Geo(const Paths &pths) :
	paths(pths)
{
	// void
}

Geo::Geo(const Points &pts)
{
	paths.push_back(Path(pts));
}

unsigned int Geo::numPaths() const {
	return paths.size();
}

// TODO CONSTANT TIME
unsigned int Geo::numPoints() const
{
	unsigned int count = 0;

	for(Paths::const_iterator it = begin(); it != end(); ++it) {
		count += it->numPoints();
	}

	return count;
}


Paths::const_iterator Geo::begin() const {
	return paths.begin();
}

Paths::const_iterator Geo::end() const {
	return paths.end();
}

void Geo::push_path(const Path& pth) {
	paths.push_back(pth); // TODO TODO: Copy or ref? BLAH.
}

