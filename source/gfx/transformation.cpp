#include "transformation.hpp"
#include "illuminator.hpp"

#include <iostream>

using namespace std;

Points get_transformed_points(Object& obj, Surface s) {
	Points outPts;
	const Points* pts = obj.getPoints();
	Position pos = obj.getPosition();
	float scale = obj.getScale();

	Illuminator* illum = obj.getIlluminator();
	Colors colors;

	for(unsigned int i = 0; i < pts->size(); i++) {
		Point pt = pts->at(i); //(*pts)[i];
		//pts[i].pos *= scale * HARDWARE_SCALE;
		pt.pos *= scale;
		pt.pos.x *= s.xScale;
		pt.pos.y *= s.yScale;
		pt.pos += pos;
		pt.pos.x += s.xShift;
		pt.pos.y += s.yShift;

		outPts.push_back(pt);
	}

	// Map illuminator colors
	if(illum) {
		colors = illum->getColors(outPts.size());
		for(unsigned int i = 0; i < outPts.size(); i++) {
			outPts[i].color = colors[i];
		}
	}

	return outPts;
}

