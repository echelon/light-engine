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
			Points::const_iterator begin() const;
			Points::const_iterator end() const;
			
		protected:
			Points points;
	};

	typedef std::vector<Path> Paths;
}

#endif
