#include "geo_blanked.hpp"
#include "geo.hpp"
#include "point.hpp"

namespace Gfx {

BlankedGeo::BlankedGeo() {
	// void
}

BlankedGeo::BlankedGeo(const Paths &pths) :
	Geo(pths)
{
	// void
}

BlankedGeo::BlankedGeo(const Points &pts) :
	Geo(pts)
{
	// void
}

} // end namespace Gfx
