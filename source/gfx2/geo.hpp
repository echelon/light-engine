#ifndef LIGHT_ENGINE_GFX2_GEO_HPP
#define LIGHT_ENGINE_GFX2_GEO_HPP

// TODO: Header files shouldn't cross-reference
#include "point.hpp"

namespace Gfx {

	/*
	 	Specify internal blanking?
			- For complex geometry, it's necessary.
			- For simple geometry, meh.

		If geometry doesn't have a point, translation, etc... what does
		it represent?

		Geo is *stateless*. It represents a line equation, GML, etc... object

		Dynamic geo has a state.

		- Can clone geo to anyone
		- Can't clone dynamic/stateful geo. Need a lower level acesss primitive

		
			FrozenGeometry 		* don't call static *
				->getIterator()
					=> GeoIterator [good design]

			DynamicGeometry
				->getGenerator()  -- no; don't permute internal state!
					OR
				->getAtTime(t) 
				->getWithParams(t, x, y, delta) 
					(or whatever)

						=> StaticGeometry

			Does geometry change as being iterated over? No!
	*/
	class StaticGeo {
		public:
			// will be constructed by a factory, GML reader, whatever...
			StaticGeo(); 

			StaticGeo(const Points &pts);

			// The number of points in the geometry
			unsigned int numPoints();

			Points::const_iterator begin();
			Points::const_iterator end();

		private:
			Points points;

		// -> get iterator over points
		// -> managed internal blanking
	};

} // end namespace Gfx

#endif
