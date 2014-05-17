#include "MatrixStack.hpp"

namespace LE {

  MatrixStack::MatrixStack() {
	stack.push_back(FourMatrix::identity());
  }

  void MatrixStack::push(const FourMatrix m) {
	stack.push_back(top() * m);
	originals.push_back(m);
  }

  void MatrixStack::pop() {
	if (originals.size() == 0) {
	  return; // Cannot pop identity matrix.
	}
	stack.pop_back();
	originals.pop_back();
  }

} // end namespace LE
