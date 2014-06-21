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
	friend class Frame;

	protected: 
	  /** Points in the geometry. */
	  Points points;

	  /** 
	   * Whether the galvo heads are expected to return to the 
	   * first point. 
	   */
	  bool returnToStart;

	public:
	  /** 
	   * CTORs 
	   */
	  Geometry() : 
		  points(),
		  returnToStart(true) {};

	  Geometry(const Points& pts) : 
		  points(pts), 
		  returnToStart(true) {};

	  Geometry(const Points& pts, const bool returnStart) : 
		  points(pts), 
		  returnToStart(true) {};

	  Geometry(const Geometry& geo) : 
		  points(geo.points),
		  returnToStart(geo.returnToStart) {};

	  /** DTOR */
	  ~Geometry() {};

	  void setPoints(const Points& pts);

	  unsigned int getNumberPoints() const;

  };
}

#endif
