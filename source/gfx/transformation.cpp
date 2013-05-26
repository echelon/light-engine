#include "transformation.hpp"
#include "illuminator.hpp"

#include <iostream>

using namespace std;

Points get_transformed_points(Object& obj, Surface s) {
	Points pts = obj.getAllPoints();
	Position pos = obj.getPosition();
	float scale = obj.getScale();

	Illuminator* illum = obj.getIlluminator();
	Colors colors;

	for(unsigned int i = 0; i < pts.size(); i++) {
		//pts[i].pos *= scale * HARDWARE_SCALE;
		pts[i].pos *= scale;
		pts[i].pos.x *= s.xScale;
		pts[i].pos.y *= s.yScale;
		pts[i].pos += pos;
		pts[i].pos.x += s.xShift;
		pts[i].pos.y += s.yShift;
	}

	// Map illuminator colors
	if(illum) {
		colors = illum->getColors(pts.size());
		for(unsigned int i = 0; i < pts.size(); i++) {
			pts[i].color = colors[i];
		}
	}

	return pts;
}

