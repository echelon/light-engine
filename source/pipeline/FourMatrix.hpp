#ifndef LE_PIPELINE_FOURMATRIX
#define LE_PIPELINE_FOURMATRIX

#include <string>
#include "../gfx/position.hpp"

// TODO - Design Goals: This should be *fast* and *easy*. 
// Methods for both in terms of memory use. But easy enough to know which
// API you're using without conflating them

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

	  /** Get identity matrix. */
	  static FourMatrix identity();

	  /** Get rotation matrices. */
	  static FourMatrix x_rotation(float theta);
	  static FourMatrix y_rotation(float theta);
	  static FourMatrix z_rotation(float theta);

	  /** Get translation matrices. */
	  static FourMatrix x_translation(float x);
	  static FourMatrix y_translation(float y);
	  static FourMatrix z_translation(float z);
	  static FourMatrix translation(float x, float y, float z);

	  /** CTOR: 4x4 zerofill. */
	  FourMatrix();

	  /** Copy CTOR. */
	  FourMatrix(const FourMatrix& mat);

	  /** DTOR. */
	  ~FourMatrix();

	  /** Matrix multiplication */
	  FourMatrix operator*(const FourMatrix& mat) const;

	  /** Multiply gfx/Position. */
	  Position multiply(const Position& pos) const;

	  /** In-place translate */
	  //void translate(float x, float y, float z);

	  /** In-place scale */
	  //void scale(float x, float y, float z);

	  /** In-place rotate in one of 3 dimensions */
	  //void rotateX(float r);
	  //void rotateY(float r);
	  //void rotateZ(float r);

	  // TODO: getTranslated[d]() -> new copy

	  /** Debug */
	  std::string toString() const;

	  /** Accessor and Mutators */
	  float getAt(unsigned int i) const;
	  void setAt(unsigned int i, float val);
	  void setAt(unsigned int row, unsigned int col, float val);
  };

  /** osteam implementation */
  std::ostream& operator <<(std::ostream& stream, const FourMatrix& mat);
}

#endif
