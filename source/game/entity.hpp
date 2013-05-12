#ifndef ETHER_DREAM_GAME_ENTITY_HPP
#define ETHER_DREAM_GAME_ENTITY_HPP

#include "../etherdream/types.hpp"

/**
 * Some basic game-support features.
 * Not necessary to use this--in fact a sophisticated game would 
 * make/utilize its own engine, but this is for demo purposes.
 */
class Entity {
	public:
		Entity():
			x(0),
			y(0),
			xVel(0.0f),
			yVel(0.0f),
			maxX(DMAX),
			maxY(DMAX),
			minX(-DMAX),
			minY(-DMAX),
			bounceBoundary(true) {};

		Entity(int _x, int _y):
			x(_x),
			y(_y),
			xVel(0.0f),
			yVel(0.0f),
			maxX(DMAX),
			maxY(DMAX),
			minX(-DMAX),
			minY(-DMAX),
			bounceBoundary(true) {};

		// Absolute positioning
		// TODO: Position struct, too!
		// SUPER TODO: float or int position and frame 
		// reference system!?
		void setPosition(int _x, int _y) {
			x = _x;
			y = _y;
		};

		// relative movement
		void move(int _x, int _y);

		// Set velocity
		void setVelocity(float xv, float yv) {
			xVel = xv;	
			yVel = yv;
		};

		// Increment position by current velocity
		// TODO: 'tick' will also handle collision detection
		// and any relevant bouncing, damage, etc. logic
		void tickVelocity();

		// Set the boundary the entity can travel
		void setBoundary(int _maxXY) {
			setBoundary(_maxXY, _maxXY, -_maxXY, -_maxXY);
		}

		// Set the boundary the entity can travel
		void setBoundary(int _maxX, int _maxY) {
			setBoundary(_maxX, _maxY, -_maxX, -_maxY);
		};

		// Set the boundary the entity can travel
		void setBoundary(int _maxX, int _maxY, int _minX, int _minY) {
			maxX = _maxX;
			maxY = _maxY;
			minX = _minX;
			minY = _minY;
		};

		int getX() { return x; };
		int getY() { return y; };

	private:
		int x;
		int y;

		float xVel;
		float yVel;

		int maxX;
		int maxY;
		int minX;
		int minY;

		// Bounce if hit boundary
		bool bounceBoundary;
		
		// TODO: Collision detection
};

#endif
