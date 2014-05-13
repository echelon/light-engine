#ifndef LE_PIPELINE_ENTITY
#define LE_PIPELINE_ENTITY

#include "../gfx/point.hpp"

namespace LE {
  class Entity {
	protected:
	  /** Points */
	  Points points;

	  /** 
	   * Until we do fully matrix math system with matrix stack, we'll do
	   * a "fixed pipeline" type of system.
	   * 
	   * In the future:
	   * matStack->pushMat(translate)
	   * matStack->pushMat(rotate)
	   * objA->draw() // or frame->draw(obj)
	   * matStack->pop()
	   */
	  int x;
	  int y;

	public: 
	  /** CTOR */
	  Entity();

	  /** DTOR. */
	  ~Entity();
  };
}

#endif
