#ifndef LIGHT_ENGINE_GFX_TRACKING_HPP
#define LIGHT_ENGINE_GFX_TRACKING_HPP

#include "point.hpp"

// TODO: This shouldn't be constant and should vary by a 
// distance heuristic
const unsigned int TRACKING_SAMPLE_PTS = 10;

/**
 * "Tracking" adds blank waypoints between two onscreen objects
 * to lessen the burden on the galvos. 
 *
 * TODO:
 * In time, these algorithms will need to become sophisticated.
 * 		- use inbound curve angle to "curve" the blanks so the
 * 		  angle isn't severe (does that really affect 2D mirrors?)
 * 		- cache tracking if objects don't move.
 * 		- floating point math bad?
 */
Points calculate_tracking_pts(const Points& a, const Points& b);

#endif
