#ifndef LIGHT_ENGINE_ASSET_RECTANGLE_HPP
#define LIGHT_ENGINE_ASSET_RECTANGLE_HPP

#include "../gfx/position.hpp"
#include "../gfx/point.hpp"
#include "../gfx/object.hpp"

using namespace std;

/**
 * TODO: 
 * 	- Any quad
 * 	- Square subclass
 * 	- Automatic and adaptive #vert/#edge
 */
class Rectangle : public Object 
{
	public:
		Rectangle(): 
			Object(),
			numEdgePoints(10),
			numVertexPoints(10),
			q1(Position(-1.0f, -1.0f)),
			q2(Position(-1.0f, 1.0f)),
			q3(Position(1.0f, 1.0f)),
			q4(Position(1.0f, -1.0f))
			{};

		Rectangle(Position a, Position b, Position c, Position d):
			Object(),
			numEdgePoints(10),
			numVertexPoints(10),
			q1(a),
			q2(b),
			q3(c),
			q4(d) {
			};

	protected:
		// How many points comprise the square 
		unsigned int numEdgePoints;
		unsigned int numVertexPoints;

		Position q1;
		Position q2;
		Position q3;
		Position q4;

		/**
		 * Generate the points of the circle.
		 */
		virtual void generateStaticPoints();

		// Generate edge
		Points getEdge(Point v1, Point v2, unsigned int num) const;
		Points getEdge(Position v1, Position v2, 
				unsigned int num) const {
			return getEdge(Point(v1, color), Point(v2, color), num);
		};


};

#endif
