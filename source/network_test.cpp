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

using namespace std;

using namespace LE;
using namespace Network;

int main() {

  Network::MacAddress mac;

  mac = MacAddress::lookup_from_ip_with_arp_table(IpAddress("169.254.97.13"), true);
  cout << "Found Mac: " << mac.toString() << endl;
  //thread dt(dac_thread);
  //dt.join();
  //

  return EXIT_SUCCESS;
}

