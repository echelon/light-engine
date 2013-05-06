#include "Dac.hpp"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <vector>

using namespace std;

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

	checkResponse('?');
}

bool Dac::prepare()
{
	prepare_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] preparing..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('p');
}

bool Dac::begin()
{
	begin_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] beginning..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('b');
}

bool Dac::stop()
{
	stop_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] stopping..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('s');
}

bool Dac::clear_estop()
{
	clear_estop_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] clearing e-stop..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('d');
}

void Dac::test_send_data(vector<dac_point> pts)
{
	data_command cmd;

	//cout << "[dac] sending data points!!!" << endl;

	cmd.set_points(pts);
	vector<uint8_t> cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	checkResponse('d');
}

bool Dac::checkResponse(char command) 
{
	dac_response rsp;
	vector<uint8_t> cmdBuf(22, 0);

	//cout << "checkResponse(" << command << ")" << endl;

	recv(fd, &cmdBuf[0], cmdBuf.size(), 0);

	rsp.setFromBuffer(cmdBuf);

	lastStatus = rsp.status;

	if(rsp.isAck()) {
		cout << "Command acknowledged (";
		cout << rsp.command << ")" << endl;
	}

	if(!rsp.isAck() || command != rsp.command) {
		//cerr << "[!] Could not do whatever: " << command << endl;
		//rsp.print();
		return false;
	}
	return true;
}
