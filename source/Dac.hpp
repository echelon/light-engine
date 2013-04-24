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
 * DAC Communication Ports
 *  - UDP broadcast and TCP data comms
 */
const int DAC_PORT_BCAST = 7654;
const int DAC_PORT_COMMS = 7765;

/**
 * Find the DAC by listening for UDP packets.
 * This is a blocking call. 
 *
 * Returns string ip_address.
 */
string find_dac();

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

		/**
		 * CTOR
		 */
		Dac(string addr);

		/**
		 * DTOR.
		 */
		~Dac();

		/**
		 * Connect, Prepare, Begin
		 */
		void connect();
		void prepare();
		void begin();

		/**
		 * Send data.
		 * TODO
		 */
		//void send();
		//void sendchar(char cmd);
		//string read(unsigned int len);
};

#endif
