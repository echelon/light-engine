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

	// Must read hello
	/*recv(fd, &rsp, sizeof rsp, 0);
	if(!rsp.isAck() || rsp.command != '?') {
		cerr << "[!] Could not connect to DAC" << endl;
		rsp.print();
	}*/
	checkResponse('?');
}

bool Dac::prepare()
{
	prepare_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] preparing..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	//recv(fd, &rsp, sizeof rsp, 0);

	checkResponse('p');

	/*if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not prepare DAC" << endl;
		rsp.print();
		return false;
	}
	return true;*/

	return true;
}

bool Dac::begin()
{
	begin_command cmd; // TODO: Could be constant
	dac_response rsp;

	vector<uint8_t> cmdBuf(7, 0);

	cout << "[dac] beginning..." << endl;

	// Messy serialization
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	/*recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not begin DAC" << endl;
		rsp.print();
		return false;
	}
	return true;*/

	return checkResponse('b');
}

bool Dac::stop()
{
	stop_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] stopping..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	/*recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not stop DAC" << endl;
		rsp.print();
		return false;
	}
	return true;*/

	return checkResponse('s');
}

bool Dac::clear_estop()
{
	clear_estop_command cmd; // TODO: Could be constant
	dac_response rsp;

	cout << "[dac] clearing e-stop..." << endl;

	send(fd, &cmd, sizeof cmd, 0);
	/*recv(fd, &rsp, sizeof rsp, 0);

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not clear e-stop" << endl;
		rsp.print();
		return false;
	}
	return true;*/

	return checkResponse('c');
}

void Dac::test_send_data(int num)
{
	//data_command* cmd = 0;
	data_command cmd;
	dac_response rsp;
	dac_point pt;

	pt.x = 100;
	pt.y = 100;
	pt.i = CMAX;
	pt.r = CMAX;
	pt.g = CMAX;
	pt.b = CMAX;

	//cmd = (data_command*)malloc(sizeof(data_command) + sizeof(dac_point)*5);

	/*cmd->npoints = 1;
	cmd->data[0] = pt;
	cmd->data[1] = pt;
	cmd->data[2] = pt;*/

	cmd.command = (uint8_t)'d';
	cmd.npoints = 1;

	cout << endl;
	for(uint i = 0; i < sizeof(cmd.data)/sizeof(dac_point); i++) {
		cout << i << " ";
		pt.x = i;
		pt.y = i;
		cmd.data[i] = pt;
		cmd.npoints = (i+1);
	}
	cout << endl;

	//cout << "sizeof struct total " << sizeof cmd << endl;
	//cout << "sizeof npoints " << sizeof cmd.npoints << endl;
	//cout << "sizeof data array " << sizeof cmd.data << endl;
	//cout << "npoints = " << cmd.npoints << endl;

	/*cout << sizeof cmd << endl;
	cout << sizeof cmd->npoints << endl;
	cout << sizeof cmd->data << endl;
	cout << endl << "MALLOC!" << endl;*/

	//*cmd.data = (dac_point*) malloc(sizeof(dac_point) * 1);

    //Packet *output = (Packet*) malloc((length+1)*sizeof(unsigned int));

	/*cout << sizeof cmd << endl;
	cout << sizeof cmd->npoints << endl;
	cout << sizeof cmd->data << endl;*/

	cout << "[dac] sending data points!!!" << endl;

	cout << cmd.command << endl;

	send(fd, &cmd, sizeof cmd, 0);

	checkResponse('d');

	cout << "SENT..." << endl;


	cout << "RECV'd..." << endl;

	if(!rsp.isAck() || cmd.command != rsp.command) {
		cerr << "[!] Could not send point" << endl;
		rsp.print();
	}
}

bool Dac::checkResponse(char command) 
{
	dac_response rsp;

	cout << "checkResponse()" << endl;

	recv(fd, &rsp, sizeof rsp, 0);

	rsp.print();

	lastStatus = rsp.status;

	if(!rsp.isAck() || command != rsp.command) {
		cerr << "[!] Could not do whatever: " << command << endl;
		//rsp.print();
		return false;
	}
	return true;
}
