#ifndef LE_PIPELINE_MATRIXSTACK
#define LE_PIPELINE_MATRIXSTACK

#include "FourMatrix.hpp"
#include <vector>

namespace LE {

  class MatrixStack {
	protected:
	  /** 
	   * Matrices are multiped with the top of the stack 
	   * upon push(). 
	   *
	   * There is an identiy matrix that always lives at 
	   * element [0] and cannot be popped off the stack. 
	   */
	  std::vector<FourMatrix> stack;

	  /** For debug, the matrices that are added. */
	  std::vector<FourMatrix> originals;

	public: 
	  MatrixStack();
	  ~MatrixStack() {};
	  
	  void push(const FourMatrix m);

	  /** Pops off the stack. */
	  void pop();

	  /** Size of the matrix stack, minus identity root. */
	  unsigned int size() const { return originals.size(); };

	  // TODO
	  //void clear() { stack.clear(); };

	  FourMatrix top() const { return stack.back(); };
  };
}

#endif
