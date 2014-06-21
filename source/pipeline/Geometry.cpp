#include "Geometry.hpp"

namespace LE {

  void Geometry::setPoints(const Points& pts) {
	points = pts;
  }

  unsigned int Geometry::getNumberPoints() const {
	return points.size();
  }

}

