#include "transformation.hpp"

Points get_transformed_points(const Object& obj) {
	Points pts = obj.getAllPoints();
	Position pos = obj.getPosition();
	float scale = obj.getScale();

	for(unsigned int i = 0; i < pts.size(); i++) {
		pts[i].pos *= scale * HARDWARE_SCALE;
		pts[i].pos += pos;
	}
	return pts;
}

