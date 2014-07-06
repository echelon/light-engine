#ifndef LE_TOOLS_BOUNCEANIMATION
#define LE_TOOLS_BOUNCEANIMATION

#include "../gfx/position.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <random>
#include <thread>

using namespace std;

/**
 * [Threadsafe]
 * Animate moving positions within a bounding box.
 * Mainly used as a tool to aid in debugging.
 */
namespace LE {
  class BounceAnimation {

	public:
	  /** CTOR. */
	  BounceAnimation(unsigned int numPositions);

	  /** DTOR. */
	  ~BounceAnimation();

	  /** Set all positions to new, random values. */
	  void randomizePositions();

	  /** Set all velocities to new, random values. */
	  void randomizeVelocities();

	  /** 
	   * Set the bounding box.
	   * Lasing coordinate space is weird: 
	   * Top is (+), Bottom is (-), but Left is (+) and Right is (-).
	   * Specified in CSS order. Cannot set Bottom > Top, Right > Left 
	   */
	  void setBoundaries(float boundaryTop, float boundaryRight, 
		  float boundaryBottom, float boundaryLeft);

	  /** Set the magnitude extrema. Min must be less than max. */
	  void setVelocityMagnitudes(float minMagnitude, float maxMagnitude);

	  /** Get the current positions. */
	  unique_ptr<vector<Position>> getPositionsUnique() const;
	  shared_ptr<vector<Position>> getPositionsShared() const;

	  /** 
	   * Start the animation thread. 
	   * This updates the positions automatically.
	   */
	  bool start();

	protected:

	  /** The positions. */
	  vector<Position> positions;

	  /** Velocities are stored in x and y. */
	  vector<Position> velocities;

	  /** Animation boundaries. See comment on mutator above. */
	  float boundaryTop;
	  float boundaryRight;
	  float boundaryBottom;
	  float boundaryLeft;

	  /** Velocity magnitude boundaries. */
	  float minVelocityMagnitude;
	  float maxVelocityMagnitude;

	  /** Random number generator and distributions. */
	  random_device random;
	  uniform_real_distribution<float> horizontal;
	  uniform_real_distribution<float> vertical;
	  uniform_real_distribution<float> magnitude;
	  bernoulli_distribution sign;

	  /** Thread sleep duration on each loop. */
	  int sleepMilliseconds;

	  /** Threading. */
	  bool threadRunning;
	  std::thread thread;
	  mutable std::mutex mutex;

	  /** The position calculation main loop. */
	  void animationThread();

	  /** Default boundaries. */
	  static const float DEFAULT_BOUNDARY_TOP;
	  static const float DEFAULT_BOUNDARY_RIGHT;
	  static const float DEFAULT_BOUNDARY_BOTTOM;
	  static const float DEFAULT_BOUNDARY_LEFT;

	  /** Default velocities */
	  static const float DEFAULT_MAX_VELOCITY_MAGNITUDE;
	  static const float DEFAULT_MIN_VELOCITY_MAGNITUDE;
  };
}

#endif
