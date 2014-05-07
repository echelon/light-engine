#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <random>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <unistd.h> // usleep

#include "network/ip_address.hpp"
#include "network/mac_address.hpp"
#include "etherdream/Dac.hpp"

using namespace std;

using namespace LE;
using namespace Network;

int main() {

  Network::MacAddress mac;

  // IP -> MAC
  // MAC -> IP
  /* Could ping subnet: 
		ip neigh flush all > /dev/null; # Clears out your arp cache
		fping -c 1 -g -q 192.168.1.0/24 2> /dev/null;  # pings all of subnet
		arp -n | grep "00:1B:4C:22:28:B1"   # Search cache for MAC address
  */
  // *OR* skip entirely and listen for UDP broadcasts and simply match the MAC!

  //mac = MacAddress::lookup_from_ip_with_arp_table(IpAddress("169.254.97.13"), true);
  //cout << "Found Mac: " << mac.toString() << endl;
  const Network::MacAddress MAC_A("00:04:A3:87:28:CD");
  const Network::MacAddress MAC_B("00:04:A3:3D:0B:60");

  Network::IpAddress ipAddress = Dac::find_broadcast_ip_with_mac(MAC_A);

  cout << "Found IP: " << ipAddress.toString() << endl;

  return EXIT_SUCCESS;
}

