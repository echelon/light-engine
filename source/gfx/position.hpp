#ifndef LIGHT_ENGINE_GFX_POSITION_HPP
#define LIGHT_ENGINE_GFX_POSITION_HPP

struct Position
{
	float x;
	float y;
	float z;

	Position(): x(0.0f), y(0.0f), z(0.0f) {};
	Position(float _x, float _y): x(_x), y(_y), z(0.0f) {};
	Position(float _x, float _y, float _z): x(_x), y(_y), z(_z) {};
	Position(const Position& p): x(p.x), y(p.y), z(p.z) {};
};

struct PhysicalPosition
{
	int x;
	int y;

	PhysicalPosition(): x(0), y(0) {};
	PhysicalPosition(int _x, int _y): x(_x), y(_y) {};
};

#endif
