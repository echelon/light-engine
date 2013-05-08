#include "Dac.hpp"
#include "../gfx/object.hpp"
#include "../gfx/point.hpp"
#include "../gfx/streamer.hpp"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <vector>

using namespace std;

// TODO: This is inefficient. 
vector<dac_point> Dac::convertPoints(Points pts)
{
	vector<dac_point> newPts;



	for(unsigned int i = 0; i < pts.size(); i++) {
		Point pt = pts[i];
		dac_point newPt;

		newPt.x = pt.x;
		newPt.y = pt.y;
		newPt.r = pt.r;
		newPt.g = pt.g;
		newPt.b = pt.b;

		newPts.push_back(newPt);
	}

	return newPts;
}

Dac::Dac(string addr) :
	fd(0),
	streamer(0),
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

	cout << "[dac] connecting... (" << address << ")" << endl;

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

// TODO: Fix messiness
void Dac::test_send_data(vector<dac_point> pts)
{
	data_command cmd;

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

void Dac::setStreamer(Streamer* s)
{
	streamer = s;
}

void Dac::stream()
{
	// TODO: Check if connected. 
	connect();

	// If can't prepare, perhaps the last run has it confused.
	// Try to stop...
	if(!prepare()) { 
		cerr << "DAC: FIRST 'PREPARE' NOT ACKNOWLEDGED!" << endl;

		// Clear any existing state!
		if(!clear_estop()) {
			// TODO: Raise critical exception
			cerr << "DAC: COULD NOT CLEAR ESTOP!" << endl;
			return;
		}

		stop();
		if(!prepare()) {
			// TODO: Raise critical exception
			cerr << "DAC: SECOND 'PREPARE' NOT ACKNOWLEDGED!" << endl;
			return;
		}
	}

	// TODO: Fuller protocol compliance. 
	/*switch(dac.lastStatus.playback_state) {
		case 2:
			cout << "DAC.lastStatus = 2" << endl;
			cout << endl;
			return EXIT_FAILURE;
			break;
		case 0:
			cout << "DAC.lastStatus = 0" << endl;
			cout << endl;
			
			// If can't prepare, perhaps the last run has it confused.
			// Try to stop...
			if(!dac.prepare()) { 
			// Stop any existing state!
				if(!dac.clear_estop()) {
					return EXIT_FAILURE; 
				}

				dac.stop();
				if(!dac.prepare()) {
					return EXIT_FAILURE; 
				}
			}
			break;
	}*/

	bool started = false;
	vector<dac_point> points;

	while(true) {
		const int SEND = 1999;
		int npoints = SEND - lastStatus.buffer_fullness;
		if(npoints < 20) {
			npoints = SEND;
		}

		points = convertPoints(streamer->getPoints(npoints));

		// TODO: points = makePoints(npoints);
		test_send_data(points);

		if(!started) {
			started = true;
			begin();
		}
	}
}

