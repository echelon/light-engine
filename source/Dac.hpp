#ifndef LASER_DAC_HPP
#define LASER_DAC_HPP

#include <string>
#include <netinet/in.h>

using namespace std;

class Dac {

	private:
		// Socket file descriptor
		int fd;

		// Dac address info
		sockaddr_in server; 

	public:
		// These are for ease of use
		const string address;
		const unsigned int port;

		/**
		 * CTOR
		 */
		Dac(string addr, unsigned int port);

		/**
		 * DTOR.
		 */
		~Dac();

		/**
		 * Send data.
		 * TODO
		 */
		void send();

		void connect();
};

#endif
