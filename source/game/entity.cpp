#include "entity.hpp"
#include <iostream>

using namespace std;

void Entity::move(int _x, int _y) 
{
	int newX = x + _x;
	int newY = x + _y;

	if(newX > maxX) {
		newX = maxX;
	}
	else if(newX < minX) {
		newX = minX;
	}

	if(newY > maxY) {
		newY = maxY;
	}
	else if(newY < minY) {
		newY = minY;
	}

	x = newX;
	y = newY;
}

void Entity::tickVelocity() 
{
	int newX = x + xVel;
	int newY = y + yVel;

	// TODO: Use sin(), cos() etc. to adjust velocities!

	if(newX > maxX) {
		newX = maxX;
		xVel = -xVel; // FIXME: Wrong
	}
	else if(newX < minX) {
		newX = minX;
		xVel = -xVel; // FIXME: Wrong
	}

	if(newY > maxY) {
		newY = maxY;
		yVel = -yVel; // FIXME: Wrong
	}
	else if(newY < minY) {
		newY = minY;
		yVel = -yVel; // FIXME: Wrong
	}

	x = newX;
	y = newY;
}

