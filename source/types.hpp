#ifndef LASER_TYPES_HPP
#define LASER_TYPES_HPP

/**
 * These types are largely defined by Jacob Potter's documentation.
 * http://ether-dream.com/protocol.html
 */

// ================================ HW CONSTANTS =============== //

const int CMAX = 65535; // Max color value

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

#endif
