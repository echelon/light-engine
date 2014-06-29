#ifndef LASER_DAC_HPP
#define LASER_DAC_HPP

#include <string>
#include <vector>
#include <memory>
#include <netinet/in.h>
#include "types.hpp"
#include "responses.hpp"
#include "commands.hpp"
#include "../gfx/point.hpp"
#include "../network/ip_address.hpp"
#include "../pipeline/FrameBuffers.hpp"
#include "../pipeline/Tracking.hpp"

class Object;
class Streamer;

namespace LE {
  namespace Network {
	class MacAddress;
  }
}

using namespace LE;
using namespace std;

/**
 * DAC 
 * Communicate with the DAC.
 */
class Dac {
  public:

	/** 
	 * Listens for broadcasting Dac matching the MAC address. 
	 * TODO: Needs timeout exception; will infinite loop!
	 *
	 * @Throws Network::SocketException
	 * @Throws Network::TimeoutException
	 */
	static Network::IpAddress find_broadcast_ip_with_mac(
		const Network::MacAddress& macAddress);

	// These are for ease of use
	const Network::IpAddress ipAddress;
	const string address;
	const unsigned int port;

	// Last status sent from DAC
	// TODO: Temporary public
	dac_status lastStatus;

	// Frame buffer
	shared_ptr<FrameBuffers> frameBuffer;

	// Tracking algorithm
	shared_ptr<Tracking> tracking;

	/** CTOR */
	Dac(const Network::IpAddress& ipAddress);

	/** CTOR (DEPRECATED) */
	Dac(const string& addr);

	/** DTOR */
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

	bool test_send_data(unique_ptr<vector<dac_point>> pts);

	/**
	 * Start the stream
	 * XXX: DEPRECATED!!!
	 * TODO: These should live outside of EtherDream code.
	 */
	void stream();
	void setStreamer(Streamer* s);

	/**
	 * Start the frame buffer stream
	 */
	void setFrameBuffer(shared_ptr<LE::FrameBuffers> frameBuffer);
	void streamFrameBuffer();

	/**
	 * Set the tracking algorithm
	 */
	void setTracking(shared_ptr<LE::Tracking> tracking);

  private:
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

	shared_ptr<vector<dac_point>> convertPoints(shared_ptr<Points> pts);

	shared_ptr<vector<dac_point>> convertPoints(
		shared_ptr<Points> trackInPts, shared_ptr<Points> pts);

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
