#ifndef LIGHT_ENGINE_GFX2_GEO_UNBLANKED_HPP
#define LIGHT_ENGINE_GFX2_GEO_UNBLANKED_HPP

#include "geo.hpp"
#include "geo_blanked.hpp" // TODO: We're about to cause cyclic dependency
#include "point.hpp"
#include "path.hpp"

namespace Gfx {

	class UnblankedGeo : public Geo
	{
		public:
			UnblankedGeo(); 
			UnblankedGeo(const Paths &pths);
			UnblankedGeo(const Points &pts); // Single Path
			//UnblankedGeo(const BlankedGeo &geo); // Unblank

			// If blanked
			bool isBlanked() const { return false; };

			BlankedGeo getBlanked() const;
	};


} // end namespace Gfx

#endif
