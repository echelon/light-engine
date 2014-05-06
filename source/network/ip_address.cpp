#include "ip_address.hpp"
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>

using namespace std;

namespace LE {
  namespace Network {

	bool IpAddress::ping(unsigned int port) const {
	  int sock = 0;
	  sockaddr_in server;

	  if (!isValid()) {
		return false;
	  }

	  server.sin_family = AF_INET;
	  server.sin_port = htons(port);
	  server.sin_addr.s_addr = inet_addr(ipString.c_str());

	  sock = socket(AF_INET, SOCK_STREAM, 0);
	  if (sock == -1) {
		return false;
	  }

	  if(connect(sock, (sockaddr*)&server, sizeof(server)) == -1) {
		close(sock);
		return false;
	  }

	  close(sock);
	  return true;
	}
  } // end namespace Network
} // end namespace LE
