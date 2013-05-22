#ifndef LASER_DAC_HPP
#define LASER_DAC_HPP

#include <string>
#include <vector>
#include <netinet/in.h>
#include "types.hpp"
#include "responses.hpp"
#include "commands.hpp"
#include "../gfx/point.hpp"
#include "../lib/etherdream.h"

class Object;
class Streamer;

using namespace std;

/**
 * DAC 
 * Communicate with the DAC.
 */
class Dac 
{
	public:
		// These are for ease of use
		const string address;
		const unsigned int port;

		// Last status sent from DAC
		// TODO: Temporary public
		DAC::dac_status lastStatus;

		/**
		 * CTOR
		 *  - string addr ip_address
		 */
		Dac(string addr);

		/**
		 * DTOR.
		 */
		~Dac();

		/**
		 * Establish TCP connection
		 */
		void connect();

		/**
		 * Commands 
		 * TODO: DOC
		 */
		bool prepare();
		bool begin();
		bool stop();
		bool clear_estop();

		bool test_send_data(vector<DAC::dac_point> pts);

		/**
		 * Start the stream
		 * TODO: These should live outside of EtherDream code.
		 */
		void stream();
		void setStreamer(Streamer* s);


	private:
		// Jacob Potter's etherdream library
		etherdream* dac; 

		// Socket file descriptor
		int fd;

		// Dac address info
		sockaddr_in server; 

		// Message buffer
		//string buffer;
		vector<char> buffer;

		// Streamer object
		Streamer* streamer;

		// Whether stream has started
		bool started;

		vector<DAC::dac_point> convertPoints(vector<Point> pts);
		void convertPoints2(vector<Point> inPts, 
				etherdream_point* outPts);

		/**
		 * Sometimes the DAC gets flooded or buffer fills.
		 * We need to reset the streaming.
		 */
		void refreshStream();

		/**
		 * Parse Response.
		 */
		bool checkResponse(char command);

};

#endif
