#include "Dac.hpp"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

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

Dac::Dac(string addr) :
	fd(0),
	address(addr),
	port(DAC_PORT_COMMS)
{
	memset(&server, 0, sizeof server);

	//fd = socket(AF_INET, SOCK_STREAM, 0);
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (fd < 0) {
		// TODO: ERROR
	}

	//connect();
}

Dac::~Dac()
{
	// TODO
}

void Dac::connect()
{
	int r = 0;
	dac_response rsp;

	cout << "[dac] connecting..." << endl;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(address.c_str());
	server.sin_port = htons(port);

    r = ::connect(fd, (sockaddr*)&server, sizeof server);

	if (r < 0) {
		// TODO ERROR
		cerr << "Could not connect() to DAC!" << endl;
		return;
	}

	// Must read hello
	recv(fd, &rsp, sizeof rsp, 0);
	if(!rsp.isAck() || rsp.command != '?') {
		cerr << "[!] Could not connect to DAC" << endl;
		rsp.print();
	}
}

bool Dac::prepare()
{
	prepare_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] preparing..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not prepare DAC" << endl;
		rsp.print();
		return false;
	}
	return true;
}

bool Dac::begin()
{
	begin_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] beginning..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not begin DAC" << endl;
		rsp.print();
		return false;
	}
	return true;
}

bool Dac::stop()
{
	stop_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] stopping..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not stop DAC" << endl;
		rsp.print();
		return false;
	}
	return true;
}

bool Dac::clear_estop()
{
	clear_estop_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] clearing e-stop..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not clear e-stop" << endl;
		rsp.print();
		return false;
	}
	return true;
}

