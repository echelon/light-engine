#include "transformation.hpp"

Points get_transformed_points(const Object& obj) {
	Points pts = obj.getAllPoints();
	Position pos = obj.getPosition();
	float scale = obj.getScale();

	for(unsigned int i = 0; i < pts.size(); i++) {
		pts[i].pos.x = pts[i].pos.x * scale * HARDWARE_SCALE + pos.x;
		pts[i].pos.y = pts[i].pos.y * scale * HARDWARE_SCALE + pos.y;
	}
	return pts;
}

