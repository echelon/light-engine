#include "FourMatrix.hpp"
#include <sstream>
#include <cmath>

// Cell aliases from:
// https://github.com/spsu/graphics4363/blob/master/source/libs/math.cpp
#define T0 0
#define T1 4
#define T2 8
#define T3 12
#define T4 1
#define T5 5
#define T6 9
#define T7 13
#define T8 2
#define T9 6
#define T10 10
#define T11 14
#define T12 3
#define T13 7
#define T14 11
#define T15 15

namespace LE {
  FourMatrix FourMatrix::identity() {
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::x_rotation(float theta) {
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	mat[4] = 0.0f;
	mat[5] = cos(theta);
	mat[6] = sin(theta);
	mat[7] = 0.0f;
	mat[8] = 0.0f;
	mat[9] = -mat[6];
	mat[10] = mat[5];
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::y_rotation(float theta) {
	float* mat = new float[16];
	mat[0] = cos(theta);
	mat[1] = 0.0f;
	mat[2] = -sin(theta);
	mat[3] = 0.0f;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;
	mat[8] = -mat[2];
	mat[9] = 0.0f;
	mat[10] = mat[0];
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::z_rotation(float theta) {
	float* mat = new float[16];
	mat[0] = cos(theta);
	mat[1] = sin(theta);
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	mat[4] = -mat[1];
	mat[5] = mat[0];
	mat[6] = 0.0f;
	mat[7] = 0.0f;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::x_translation(float x) {
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = x;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::y_translation(float y) {
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = y;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::z_translation(float z) {
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = z;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix FourMatrix::translation(float x, float y, float z) {
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = x;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = y;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = z;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	return FourMatrix(mat);
  }

  FourMatrix::~FourMatrix() {
	delete[] values;
  }

  FourMatrix::FourMatrix() {
	// TODO: inline initialization
	values = new float[16];
	for(unsigned int i = 0; i < 16; i++) {
	  values[i] = 0.0f;
	}
  }

  FourMatrix::FourMatrix(const FourMatrix& mat) {
	values = new float[16];
	for(unsigned int i = 0; i < 16; i++) {
	  values[i] = mat.values[i];
	}
  }

  // PRIVATE
  FourMatrix::FourMatrix(float* array) {
	values = array;
  }

  // TODO: Allocation and copy... bad?
  FourMatrix FourMatrix::operator*(const FourMatrix& mat) const {
	float* a = values;
	float* b = mat.values;
	float* r = new float[16];

	r[T0] = a[T0]*b[T0]+a[T1]*b[T4]+a[T2]*b[T8]+a[T3]*b[T12];
	r[T1] = a[T0]*b[T1]+a[T1]*b[T5]+a[T2]*b[T9]+a[T3]*b[T13];
	r[T2] = a[T0]*b[T2]+a[T1]*b[T6]+a[T2]*b[T10]+a[T3]*b[T14];
	r[T3] = a[T0]*b[T3]+a[T1]*b[T7]+a[T2]*b[T11]+a[T3]*b[T15];

	r[T4] = a[T4]*b[T0]+a[T5]*b[T4]+a[T6]*b[T8]+a[T7]*b[T12];
	r[T5] = a[T4]*b[T1]+a[T5]*b[T5]+a[T6]*b[T9]+a[T7]*b[T13];
	r[T6] = a[T4]*b[T2]+a[T5]*b[T6]+a[T6]*b[T10]+a[T7]*b[T14];
	r[T7] = a[T4]*b[T3]+a[T5]*b[T7]+a[T6]*b[T11]+a[T7]*b[T15];

	r[T8] = a[T8]*b[T0]+a[T9]*b[T4]+a[T10]*b[T8]+a[T11]*b[T12];
	r[T9] = a[T8]*b[T1]+a[T9]*b[T5]+a[T10]*b[T9]+a[T11]*b[T13];
	r[T10] = a[T8]*b[T2]+a[T9]*b[T6]+a[T10]*b[T10]+a[T11]*b[T14];
	r[T11] = a[T8]*b[T3]+a[T9]*b[T7]+a[T10]*b[T11]+a[T11]*b[T15];

	r[T12] = a[T12]*b[T0]+a[T13]*b[T4]+a[T14]*b[T8]+a[T15]*b[T12];
	r[T13] = a[T12]*b[T1]+a[T13]*b[T5]+a[T14]*b[T9]+a[T15]*b[T13];
	r[T14] = a[T12]*b[T2]+a[T13]*b[T6]+a[T14]*b[T10]+a[T15]*b[T14];
	r[T15] = a[T12]*b[T3]+a[T13]*b[T7]+a[T14]*b[T11]+a[T15]*b[T15];

	// TODO: Stupid impl. Will call copy CTOR then DTOR. Doubly owned!
	return FourMatrix(r); 
  }

  //void FourMatrix::translate(float x, float y, float z) {
  //}

  std::string FourMatrix::toString() const {
	std::ostringstream ss;
	// TODO: loop inefficient
	for(int i = 0; i < 16; i++) {
	  ss << values[i] << "\t";
	  if(i % 4 == 3) {
		ss << "\n";
	  } else {
		ss << "\t";
	  }
	}
	return ss.str();
  }

  float FourMatrix::getAt(unsigned int i) const {
	return values[i]; // TODO: Bounds assertions
  }

  void FourMatrix::setAt(unsigned int i, float val) {
	values[i] = val; // TODO: Bounds assertions
  }

  void FourMatrix::setAt(unsigned int row, unsigned int col, float val) {
	unsigned int cell = row * 4 + col; // TODO: Bounds assertions
	values[cell] = val;
  }
} // end namespace

