#include "Frame.hpp"
#include <iostream>

using namespace std;

namespace LE {
  Frame::Frame() :
	points(),
	mode(NONE)
  {
	cout << points.size() << endl;
  }

  Frame::~Frame() {
  }

  unsigned int Frame::getNumberPoints() const {
	return points.size();
  }

  void Frame::draw(const Geometry& geo) {
	points.insert(points.begin(), geo.points.begin(), geo.points.end());
  }

  void Frame::draw(const Geometry& geo, const MatrixStack& matStack) {
  }

  void Frame::clear() {
	points.resize(0); // Doesn't change space allocation!
  }

  Points Frame::getPoints() const {
	return points; // TODO CONFIRM
  }

} // end namespace LE

