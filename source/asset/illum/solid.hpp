#ifndef LIGHT_ENGINE_ASSET_ILLUM_SOLID_HPP
#define LIGHT_ENGINE_ASSET_ILLUM_SOLID_HPP

#include "../../gfx/illuminator.hpp"
#include "../../gfx/color.hpp"

/**
 * Generates a solid color.
 * TODO: Kind of wasteful... make a switch for solid colors 
 * and illuminators
 */
class SolidIlluminator : public Illuminator
{
	public:
		SolidIlluminator(const Object& o, Color c): 
			Illuminator(o),
			color(c) 
			{};
	
		virtual Colors getColors(unsigned int num) const {
			Colors colors(num, color);
			return colors;
		};

	protected:
		Color color;
};

#endif
