#ifndef LASER_RESPONSES_HPP
#define LASER_RESPONSES_HPP

#include <iostream>

using namespace std;

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

	dac_status():
		protocol('x'),
		light_engine_state('x'),
		playback_state('x'),
		source('x'),
		light_engine_flags('x'),
		playback_flags('x'),
		source_flags('x'),
		buffer_fullness('x'),
		point_rate('x'),
		point_count('x') {};
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
	dac_status status;
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

	dac_status status;

	dac_response():
		response('x'),
		command('x'),
		status() {}; 

	/**
	 * Whether the response is an Ack.
	 */
	bool isAck() { return response == 'a'; };

	void print() {
		cout << "DAC Response" << endl;
		cout << "  response:\t\t" << response << endl;
		cout << "  command:\t\t" << command << endl;
		cout << "  -------- status -------" << endl;
		cout << "    protocol:\t\t" << status.protocol << endl;
		cout << "    light_engine_state:\t"
			 << status.light_engine_state << endl;
		cout << "    playback_state:\t"
			 << status.playback_state << endl;
		cout << "    light_engine_flags:\t"
			 << status.light_engine_flags << endl;
		cout << "    playback_flags:\t"
			 << status.playback_flags << endl;
		cout << "    source_flags:\t"
			 << status.source_flags << endl;
		cout << "    buffer_fullness:\t"
			 << status.buffer_fullness << endl;
		cout << "    source:\t\t"
			 << status.source << endl;
		cout << "    point_rate:\t\t" 
			 << status.point_rate << endl;
		cout << "    point_count:\t"
			 << status.point_count << endl;
	};
};

#endif
