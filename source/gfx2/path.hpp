#ifndef LIGHT_ENGINE_GFX2_PATH_HPP
#define LIGHT_ENGINE_GFX2_PATH_HPP

#include <vector>
#include "point.hpp"

namespace Gfx {

	class Path
	{
		public:
			Path();
			Path(const Points &pts);

			// The number of points in the geometry
			unsigned int numPoints() const;

			// Iterator to Point(s)
			// XXX/TODO: Perhaps we shouldn't force const access!
			// Isn't the streamer algorithm deciding to use const access?
			// I should be able to manipulate these as a client lib.
			// I can just provide 'const' declarations when necessary.
			Points::const_iterator begin() const;
			Points::const_iterator end() const;

			// Remove all points in the path (destructive!)
			void reset();

		protected:
			Points points;
	};

	typedef std::vector<Path> Paths;
}

#endif
