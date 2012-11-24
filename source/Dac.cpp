#include "Dac.hpp"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

using namespace std;

Dac::Dac(string addr, unsigned int port) :
	fd(0),
	address(addr),
	port(port)
{
	memset(&server, 0, sizeof server);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (fd < 0) {
		// TODO: ERROR
	}

	connect();
}

Dac::~Dac()
{
	// TODO
}

void Dac::connect()
{
	int r = 0;

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, address.c_str(), 
			&server.sin_addr);

    r = ::connect(fd, (sockaddr*)&server, sizeof server);

	if (r < 0) {
		// TODO ERROR
		cerr << "Could not connect() to DAC!" << endl;
		return;
	}
}

void Dac::send()
{
	// TODO
	//
	//ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	
	char buf [1024];

	memset(&buf, 0, sizeof(buf));

	cout << buf << endl;

	write(fd, buf, strlen(buf));

	read(fd, buf, strlen(buf));

	cout << buf << endl;

}
