#ifndef LIGHT_ENGINE_GFX2_GEO_BLANKED_HPP
#define LIGHT_ENGINE_GFX2_GEO_BLANKED_HPP

#include "geo.hpp"
#include "point.hpp"
#include "path.hpp"

namespace Gfx {

	class BlankedGeo : public Geo
	{
		public:
			BlankedGeo(); 
			BlankedGeo(const Paths &pths);
			BlankedGeo(const Points &pts); // Single Path
			//BlankedGeo(const UnblankedGeo &geo); // Unblank

			// If blanked
			bool isBlanked() const { return true; };

	};


} // end namespace Gfx

#endif
