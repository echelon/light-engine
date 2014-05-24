#include "geo_unblanked.hpp"
#include "geo.hpp"
#include "point.hpp"

namespace Gfx {

UnblankedGeo::UnblankedGeo() {
	// void
}

UnblankedGeo::UnblankedGeo(const Paths &pths) :
	Geo(pths)
{
	// void
}

UnblankedGeo::UnblankedGeo(const Points &pts) :
	Geo(pts)
{
	// void
}

BlankedGeo UnblankedGeo::getBlanked() const
{
	BlankedGeo bgeo;
	Path blank;

	for(Gfx::Paths::const_iterator it = begin(); it != end(); ++it) {
		Path p = *it;

		p.reset();

		bgeo.push_path(p); // TODO: Is this a reference?!
		bgeo.push_path(p); // TODO: Is this a reference?!
	}

	return bgeo;
}

} // end namespace Gfx
