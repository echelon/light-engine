#ifndef LASER_COMMANDS_HPP
#define LASER_COMMANDS_HPP

// These types are largely defined by Jacob Potter's documentation.
// http://ether-dream.com/protocol.html

/**
 * Prepare Stream
 * 	- Resets buffer to empty and 
 * 	- sets point_count = 0
 * 	- Only if LE is Ready and playback sys is Idle
 */
struct prepare_command {
	uint8_t command; // 'p'

	prepare_command(): command('p') {};
};

/**
 * Begin Playback
 *  - Begin producing output
 *  - point_rate: number of points per second to read
 *    from the buffer. (mine is 30kpps)
 */
struct begin_command {
	uint8_t command;		 // 'b'
	uint16_t low_water_mark; // Unused; future use
	uint32_t point_rate;	 // *NOT* hw scan rate! streamed pps.

	begin_command(): 
		command('b'),
		low_water_mark(0),
		point_rate(30000) {};
};

/**
 * Queue Rate Change
 *  - Adds a new point rate to the point rate buffer.
 *    Point rate changes are read out of buffer when 
 *    a point with appropriate flag is played. 
 */
struct queue_change_command {
	uint8_t command;		// 'q'
	uint32_t point_rate;	// *NOT* hw scan rate! streamed pps.

	queue_change_command():
		command('q'),
		point_rate(0) {};
};

/**
 * Point
 *  - If control bit 15 is set and there is a point rate change
 *    in the point rate change buffer, set as current playback
 *    rate.
 *  - Color scale is [0, 35535]
 */
struct dac_point {
	uint16_t control; // TODO: Should we change rate at turns, etc?
	uint16_t x;
	uint16_t y;
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t u1;
	uint16_t u2;

	dac_point():
		control(0),
		x(0),
		y(0),
		r(0),
		g(0),
		b(0),
		u1(0),
		u2(0) {};
};

/**
 * Write Data
 *  - Provide data to DAC buffer
 */
struct data_command {
	uint8_t command; // 'd'
	uint16_t npoints;
	struct dac_point data[];
};

// !!! scanrate != pointrate
// point rate -- how fast computer outps image data, *NOT* hw tuning!
// 				 varies within the show!
//

/**
 * Stop
 * 	- immediately stop play and return to idle
 * 	- TODO: E-Stop, Clear E-Stop
 */
struct stop_command {
	uint8_t command; // 's'

	stop_command():
		command('s') {};
};

/**
 * Keep Alive
 *  - for when DAC not actively streaming
 */
struct keep_alive_command {
	uint8_t command; // '?'

	keep_alive_command():
		command('?') {};
};

#endif
