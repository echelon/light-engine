#ifndef LASER_DAC_HPP
#define LASER_DAC_HPP

#include <string>
#include <vector>
#include <netinet/in.h>
#include "types.hpp"
#include "responses.hpp"
#include "commands.hpp"

using namespace std;

/**
 * DAC 
 * Communicate with the DAC.
 */
class Dac {

	private:
		// Socket file descriptor
		int fd;

		// Dac address info
		sockaddr_in server; 

		// Message buffer
		//string buffer;
		vector<char> buffer;


	public:
		// These are for ease of use
		const string address;
		const unsigned int port;

		// Last status sent from DAC
		// TODO: Temporary public
		dac_status lastStatus;

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

		void test_send_data(vector<dac_point> pts);

		/**
		 * Parse Response.
		 */
		bool checkResponse(char command);
};

#endif
