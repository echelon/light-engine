#ifndef LE_PIPELINE_FOURMATRIX
#define LE_PIPELINE_FOURMATRIX

#include <string>

namespace LE {
  class FourMatrix {

	protected:
	  // TODO: not sure if good implementation
	  float* values;

	  /**
	   * Unsafe ownership-taking CTOR.
	   * MUST be an array of 16.
	   * Internal use only.
	   */
	  FourMatrix(float* array);

	public:
	  /** CTOR: 4x4 */
	  FourMatrix();

	  /** Copy CTOR */
	  FourMatrix(const FourMatrix& mat);

	  /** DTOR */
	  ~FourMatrix();

	  FourMatrix operator*(const FourMatrix& mat) const;

	  /** Debug */
	  std::string toString() const;

	  /** Accessor and Mutator */
	  void setAt(unsigned int i, float val);
	  void setAt(unsigned int row, unsigned int col, float val);
	  float getAt(unsigned int i) const;
  };
}

#endif
