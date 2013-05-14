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
			edge(1.0f), 
			numEdgePoints(10), 
			numVertexPoints(15) {};

		Square(float ed):
			Object(),
			edge(ed), 
			numEdgePoints(10), 
			numVertexPoints(15) {};

		Square(float ed, int nedge, int nvert):
			Object(),
			edge(ed), 
			numEdgePoints(nedge), 
			numVertexPoints(nvert) {};

		virtual Points getAllPoints();


	protected:
		// Edge <= (0.0, 1.0] 
		float edge;

		// How many points comprise the square 
		unsigned int numEdgePoints;
		unsigned int numVertexPoints;

		// Generate edge
		Points getEdge(Point v1, Point v2, int num);
};

#endif
