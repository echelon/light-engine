#ifndef LIGHT_ENGINE_GFX_ILLUMINATOR_HPP
#define LIGHT_ENGINE_GFX_ILLUMINATOR_HPP

#include "object.hpp"
#include "color.hpp"
#include <iostream>

using namespace std;

/**
 * Illuminator
 * Generates color patterns for objects so that objects 
 * don't have to be rendered in boring monochrome.
 *
 * They may store state, but not between two illuminators.
 */

class Illuminator
{
	public:
		/**
		 * CTOR and DTOR
		 */
		Illuminator(const Object& _o) : object(_o) {};

		~Illuminator() {};

		/**
		 * Get the colors for the frame.
		 */
		virtual Colors getColors(unsigned int num) const {
			Colors colors(num, INVISIBLE);
			cerr << "WRONG getColors()" << endl;
			return colors;
		};

	protected:

		const Object& object;

		// TODO: For now points cannot be dropped.
		int numPoints;
};

#endif
