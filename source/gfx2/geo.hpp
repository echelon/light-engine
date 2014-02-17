#ifndef LIGHT_ENGINE_GFX2_GEO_HPP
#define LIGHT_ENGINE_GFX2_GEO_HPP

// TODO: Header files shouldn't cross-reference
#include "point.hpp"
#include "path.hpp"

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

    ------------------------------------------------------------

	Do we want to represent blank points?

		<x, y, z, rgb=None> ?

			Conflating geometry and color again.

	Perhaps we'll have a vector of vectors.
		- But how do clients utilize?
		- Do we flatten the iterator?
			- Kind of useless. (Very useless, really.)
		- But where does blanking come from?

	Assume all Geometry consists of one or more lines.
		- Each of these lines should be indexable
			- (eg. to provide color later)

		- Each line will have a computed complexity metric and can 
		  manage itself

	XXX: Could insert a "BlankPath" into Paths for precalculated blanking!
*/

namespace Gfx {

	class StaticGeo 
	{
		public:
			// CTOR -- will be built by a factory (eg. GML parser)
			StaticGeo(); 
			StaticGeo(const Paths &pths);
			StaticGeo(const Points &pts); // Single Path

			// The number of paths in the geometry
			unsigned int numPaths() const;
			unsigned int numPoints() const;

			// Iterator to Path(s)
			Paths::const_iterator begin() const;
			Paths::const_iterator end() const;

		private:
			//Points points;
			Paths paths;

		// -> get iterator over points
		// -> managed internal blanking
	};

} // end namespace Gfx

#endif
