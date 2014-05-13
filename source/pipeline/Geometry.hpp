#ifndef LE_PIPELINE_GEOMETRY
#define LE_PIPELINE_GEOMETRY

#include "../gfx/point.hpp"
#include "../gfx/object.hpp"

/**
 * TODO: The plan is to deprecate 'gfx/point' and 'gfx/object',
 * making this the all-inclusive for graphics geometry. Eventually
 * even 3D perspective.
 */
namespace LE {
  class Geometry {
	protected: 
	  Points points;

	public:
	  /** 
	   * CTORs 
	   */
	  Geometry() {};
	  Geometry(const Points& pts) : points(pts) {};
	  //Geometry(const Object& obj) : points(obj.getPoints()) {};

	  /** DTOR */
	  ~Geometry() {};
  };
}

#endif
