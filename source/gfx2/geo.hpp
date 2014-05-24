#ifndef LIGHT_ENGINE_GFX2_GEO_HPP
#define LIGHT_ENGINE_GFX2_GEO_HPP

// TODO TODO TODO
// DESCRIPTION OF WORK HERE --
// 1) I'm going to create the types and containers for holding point data
//		including sub-geometry, static/dynamic, etc.
// 2) Then I'm going to consider how to add blanking data info
// 3) Then I'll figure out color
// Future) Int-vs-float, physical-vs-logical (far future!)


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

	
		FrozenGeometry 
			->getIterator()
				=> GeoIterator [good design]

		DynamicGeometry
			->getGenerator()  -- no; don't permute internal state!
				OR
			->getAtTime(t) 
			->getWithParams(t, x, y, delta) 
				(or whatever)

					=> Geometry

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

	class Geo 
	{
		public:
			// CTOR -- will be built by a factory (eg. GML parser)
			Geo(); 
			Geo(const Paths &pths);
			Geo(const Points &pts); // Single Path

			// The number of paths in the geometry
			unsigned int numPaths() const;
			unsigned int numPoints() const;

			// Iterator to Path(s)
			// XXX/TODO: Perhaps we shouldn't force const access!
			// Isn't the streamer algorithm deciding to use const access?
			// I should be able to manipulate these as a client lib.
			// I can just provide 'const' declarations when necessary.
			Paths::const_iterator begin() const;
			Paths::const_iterator end() const;

			// TODO: Allow manipulation of state?
			void push_path(const Path &pth);

			// If blanked
			bool isBlanked() const { return false; };

		protected:
			Paths paths;
			//Points points;
			//unsigned int cashedNumPoints; // TODO

		// -> get iterator over points
		// -> managed internal blanking
	};

} // end namespace Gfx

#endif
