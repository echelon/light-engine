#ifndef LE_GFX_POSITION
#define LE_GFX_POSITION

#include <vector> 
#include <sstream>

struct Position
{
  float x;
  float y;
  float z;

  Position(): x(0.0f), y(0.0f), z(0.0f) {};
  Position(float _x, float _y): x(_x), y(_y), z(0.0f) {};
  Position(float _x, float _y, float _z): x(_x), y(_y), z(_z) {};
  Position(const Position& p): x(p.x), y(p.y), z(p.z) {};

  const Position operator+(const Position& p) const {
	Position r;
	r.x = x + p.x;
	r.y = y + p.y;
	r.z = z + p.z;
	return r;
  };

  const Position operator-(const Position& p) const {
	Position r;
	r.x = x - p.x;
	r.y = y - p.y;
	r.z = z - p.z;
	return r;
  };

  const Position operator*(float n) const {
	Position r;
	r.x = x * n;
	r.y = y * n;
	r.z = z * n;
	return r;
  };

  const Position operator/(float n) const {
	Position r;
	r.x = x / n;
	r.y = y / n;
	r.z = z / n;
	return r;
  };

  Position& operator+=(const Position& p) {
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
  };

  Position& operator-=(const Position& p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
  };

  Position& operator*=(float n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
  };

  Position& operator/=(float n) {
	x /= n;
	y /= n;
	z /= n;
	return *this;
  };

  friend inline std::ostream& operator <<(std::ostream& stream, 
	  const Position& pos) {
	return stream << "<Position: " << pos.x << ", " << pos.y << ">";
  };
};

typedef std::vector<Position> Positions;

#endif
