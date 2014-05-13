#ifndef LE_PIPELINE_STREAMER
#define LE_PIPELINE_STREAMER

#include <memory>
#include <vector>
#include "Frame.hpp"

namespace LE {
  class Entity;

  class Streamer {
	protected:
	  /** Entities for drawing. */
	  std::vector<std::shared_ptr<Entity>> entities;

	  /** Frames. */
	  Frame frameA;
	  Frame frameB;

	  // TODO

	public:
	  /** CTOR */
	  //Streamer();

	  /** DTOR */
	  //~Streamer();

	  /** Add entity */
	  void addEntity(std::shared_ptr<Entity> entity);

	  /**
	   * Calculate the next frame and mark it ready to swap in
	   */
	  void calculateAndSwap();

	  //bool removeEntity(std::shared_ptr<Entity> entity);

	  /** Clear the streamer of entities. */
	  void clear() { entities.clear(); };

	  /** Is vector empty? */
	  bool empty() const { return entities.empty(); };

	  /** Size of entities vector. */
	  size_t size() const { return entities.size(); };

	private:

	  /** Calculate the frame. */
	  //void doCalculate();
  };
}
#endif
