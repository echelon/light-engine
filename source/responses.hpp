#ifndef LASER_RESPONSES_HPP
#define LASER_RESPONSES_HPP

// These types are largely defined by Jacob Potter's documentation.
// http://ether-dream.com/protocol.html

/**
 * DAC Status Report
 */
struct dac_status {
	uint8_t protocol;
	uint8_t light_engine_state;	// LIGHT_ENGINE_STATE
	uint8_t playback_state;		// PLAYBACK_STATE
	uint8_t source;				// 0 network; 1 ILDA/SD; 2 internal

	// TODO: Flag handling
	uint16_t light_engine_flags;
	uint16_t playback_flags;
	uint16_t source_flags;

	uint16_t buffer_fullness; 	// Num points currently buffered
	uint32_t point_rate;		// Current pps
	uint32_t point_count;		// Num points played so far
};

/**
 * DAC UDP Broadcasts (1/second)
 */
struct dac_broadcast {
	uint8_t mac_address[6];
	uint16_t hw_revision;
	uint16_t sw_version;
	uint16_t buffer_capacity;
	uint32_t max_point_rate;
	struct dac_status status;
};

/**
 * Dac Response
 */
struct dac_response {
	// Ack/Nak response
	// 	- 'a' is Ack; previous command accepted.
	// 	- 'f' is Nak/Full; buffer too full for last command.
	// 	- 'i' is Nak/Invalid; last command was invalid
	// 	- '!' is Nak/Stop; emergency stop condition
	uint8_t response;

	// Echo back of previously sent command
	uint8_t command;

	struct dac_status status;
};

#endif
