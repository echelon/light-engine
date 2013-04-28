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

	// Sent over socket
	vector<uint8_t> serialize() {
		vector<uint8_t> buf(7, 0);

		buf[0] = command;
		buf[1] = low_water_mark >> 0;
		buf[2] = low_water_mark >> 8;
		buf[3] = point_rate >> 0;
		buf[4] = point_rate >> 8;
		buf[5] = point_rate >> 16;
		buf[6] = point_rate >> 24;

		return buf;
	}
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
	uint16_t i;
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t u1;
	uint16_t u2;

	dac_point():
		control(0),
		x(0),
		y(0),
		i(0),
		r(0),
		g(0),
		b(0),
		u1(0),
		u2(0) {};

	// Sent over socket
	vector<uint8_t> serialize() {
		vector<uint8_t> buf(18, 0);

		buf[0] = control >> 0;
		buf[1] = control >> 8;
		buf[2] = x >> 0;
		buf[3] = x >> 8;
		buf[4] = y >> 0;
		buf[5] = y >> 8;
		buf[6] = i >> 0;
		buf[7] = i >> 8;
		buf[8] = r >> 0;
		buf[9] = r >> 8;
		buf[10] = g >> 0;
		buf[11] = g >> 8;
		buf[12] = b >> 0;
		buf[13] = b >> 8;
		buf[14] = u1 >> 0;
		buf[15] = u1 >> 8;
		buf[16] = u2 >> 0;
		buf[17] = u2 >> 8;

		return buf;
	}
};

/**
 * Write Data
 *  - Provide data to DAC buffer
 */
struct data_command {
	uint8_t command; // 'd'
	uint16_t npoints;
	dac_point data[50]; // XXX: Good c99, *BAD* C++!

	// Since C++ creates these for us, prevent misuse
	//private:
		//void data_command(const data_command&) {};
		//void operator=(const data_command&) {};


	// Sent over socket
	vector<uint8_t> serialize() {
		vector<uint8_t> buf(3 + 50*18, 0);
		vector<uint8_t> ptBuf(18, 0);

		buf[0] = command;
		buf[1] = npoints >> 0;
		buf[2] = npoints >> 8;

		for(unsigned int i = 0; i < 50; i++) {
			data[i].r = CMAX;
			data[i].g = CMAX;
			data[i].b = CMAX;
			ptBuf = data[i].serialize();
			for(unsigned int j = 0; j < 18; j++) {
				buf[3 + i*18 + j] = ptBuf[j];
			}

		}
		return buf;
	}
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

struct clear_estop_command {
	uint8_t command; // 'c'

	clear_estop_command():
		command('c') {};
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
