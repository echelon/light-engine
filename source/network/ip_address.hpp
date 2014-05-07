#ifndef LE_NETWORK_IP_ADDRESS
#define LE_NETWORK_IP_ADDRESS

#include <string>

namespace LE {
  namespace Network {

	// IPv4 Addresses
	class IpAddress {

	  public:
		/** CTOR. */
		IpAddress(): ipString("") {};
		IpAddress(std::string ipAddress): ipString(ipAddress) {};

		/** Ping the IP on the port. Not the same as "PING" commmand. */
		// TODO: Synchronous, so needs timeout spec.
		// TODO: Const correctness. Doesn't affect program state, but does 
		// affect system
		bool ping(unsigned int port) const;

		std::string toString() const { return ipString; };

		/** Valid IP address heuristic. */
		bool isValid() const {
		  // TODO: Actually parse and evaluate; cache result.
		  return (ipString.size() > 6);
		}

	  protected:
		std::string ipString;

	};

  }
}

#endif
