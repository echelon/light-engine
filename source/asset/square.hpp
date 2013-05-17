#ifndef LIGHT_ENGINE_ASSET_SQUARE_HPP
#define LIGHT_ENGINE_ASSET_SQUARE_HPP

#include <vector>
#include "../gfx/point.hpp"
#include "../gfx/object.hpp"

using namespace std;

class Square: public Object 
{
	public:
		Square(): 
			Object(),
			numEdgePoints(10), 
			numVertexPoints(15) {};

		Square(int nedge, int nvert):
			Object(),
			numEdgePoints(nedge), 
			numVertexPoints(nvert) {};

		virtual Points getAllPoints() const;


	protected:
		// How many points comprise the square 
		unsigned int numEdgePoints;
		unsigned int numVertexPoints;

		// Generate edge
		Points getEdge(Point v1, Point v2, int num) const;
};

#endif
