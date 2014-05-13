#include "Streamer.hpp"
#include "Entity.hpp"
#include "Frame.hpp"

namespace LE {

  void Streamer::addEntity(std::shared_ptr<Entity> entity) {
	entities.push_back(entity);
  }

  void Streamer::calculateAndSwap() {
  }

} // end namespace LE

