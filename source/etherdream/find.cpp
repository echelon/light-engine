#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include "types.hpp"

using namespace std;

string find_dac()
{
	int fd = 0, 
		r = 0;
	char buf[1024];
	char ipstr[INET_ADDRSTRLEN];

	sockaddr_in client, 
				sender;
	socklen_t sendsize = sizeof sender;

	memset(&sender, 0, sizeof sender);
	memset(&client, 0, sizeof client);
	memset(&buf, 0, sizeof buf);

	client.sin_family = AF_INET;
	client.sin_port = htons(DAC_PORT_BCAST);
	client.sin_addr.s_addr = INADDR_ANY;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (fd < 0) {
		return ""; // TODO ERROR
	}

	r = bind(fd, (sockaddr*)&client, sizeof(client));

	if (r < 0) {
		return ""; // TODO ERROR
	}

	recvfrom(fd, buf, sizeof buf, 0, 
			(sockaddr*)&sender, &sendsize);
	
	return inet_ntop(AF_INET, &sender.sin_addr, 
			ipstr, sizeof ipstr);
}

