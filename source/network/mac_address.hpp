#include <string>

namespace LE {
  namespace Network {
	class IpAddress;
	class MacAddress {
	  // TODO

	  public: 
		/** Static lookup of the MAC address from the given IP. */
		static MacAddress lookup_from_ip(const IpAddress& ipAddress);
		static MacAddress lookup_from_ip_with_arp_table(const IpAddress& ipAddress, 
			bool ping=true);

		/** CTOR */
		MacAddress() : macString("") {};
		MacAddress(std::string macAddress) : macString(macAddress) {};

		std::string toString() const { return macString; };

		/** Whether MAC appears valid. */
		bool isValid() const {
		  // TODO: Actually check hex and other fields; cache result
		  return (macString.size() == 17);
		}

	  protected:
		std::string macString; // In AA:BB:CC:DD:EE:FF format
	};
  }
}

