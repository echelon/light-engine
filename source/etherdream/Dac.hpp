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
		/**
		 * CTOR
		 *  - string addr ip_address
		 */
		Dac();
		~Dac();

		/**
		 * Establish TCP connection
		 */
		void connect();

		/**
		 * Set the streamer object.
		 *  - Streamers autoblank, etc.
		 */
		void setStreamer(Streamer* s);

		/**
		 * Start the stream
		 * TODO: These should live outside of EtherDream code.
		 */
		void stream();


	private:
		// Jacob Potter's etherdream library
		etherdream* dac; 

		// Streamer object
		Streamer* streamer;

		void convertPoints(Points inPts, 
				etherdream_point* outPts);
};

#endif
