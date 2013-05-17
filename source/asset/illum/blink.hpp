#ifndef LIGHT_ENGINE_ASSET_ILLUM_BLINK_HPP
#define LIGHT_ENGINE_ASSET_ILLUM_BLINK_HPP

#include "../../gfx/illuminator.hpp"
#include "../../gfx/color.hpp"

/**
 * Generates a solid color.
 * TODO: Kind of wasteful... make a switch for solid colors 
 * and illuminators
 */
class BlinkIlluminator : public Illuminator
{
	public:
		BlinkIlluminator(const Object& o, Colors c, 
				unsigned int _cycles = 5) :
			Illuminator(o),
			colors(c),
			cycles(_cycles)
			{};

		BlinkIlluminator(const Object& o, Color c1, Color c2,
				unsigned int _cycles = 5) :
			Illuminator(o),
			cycles(_cycles)
			{
				colors.push_back(c1);
				colors.push_back(c2);
			};
	
		virtual Colors getColors(unsigned int num) const {
			Colors cols;
			Color col;
			unsigned int ppcyc = num / cycles;
			unsigned int ppcol = ppcyc / colors.size();
			//unsigned int every = num / (cycles * colors.size());
			for(unsigned int i = 0; i < num; i++) {
				unsigned int ci = (i % ppcyc) / ppcol;
				col = colors[ci];
				cols.push_back(col);
			}
			return cols;
		};

	protected:
		Colors colors;
		unsigned int cycles;
};

#endif
