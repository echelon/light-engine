#ifndef LASER_TYPES_HPP
#define LASER_TYPES_HPP

/**
 * These types are largely defined by Jacob Potter's documentation.
 * http://ether-dream.com/protocol.html
 */

// ================================ HW CONSTANTS =============== //

namespace DAC {

/**
 * DAC Communication Ports
 *  - UDP broadcast and TCP data comms
 */
const int DAC_PORT_BCAST = 7654;
const int DAC_PORT_COMMS = 7765;

/**
 * Color and dimension magnitude ranges.
 */
const int CMAX = 65535; // Max color value (unsigned)
const int DMAX = 32760; // TODO: This is wrong! (signed)

enum LIGHT_ENGINE_STATE {
	READY		= 0,
	WARMUP		= 1,
	COOLDOWN	= 2,
	EMERGENCY	= 3,
};

enum PLAYBACK_STATE {
	IDLE		= 0,
	PREPARED	= 1,
	PLAYING		= 2,
};

//enum SOURCE_STATE = {
//};

/**
 * Commands to send to DAC
 */
enum COMMAND {
	PREPARE 			= 'p',
	BEGIN_PLAYBACK		= 'b',
	QUEUE_RATE_CHANGE	= 'q',
	WRITE_DATA 			= 'd',
	STOP				= 's',
	ESTOP				= 0x00,
	ESTOP2				= 0xFF,
	CLEAR_ESTOP			= 'c',
	PING				= '?',
};

} // end namespace DAC

#endif
