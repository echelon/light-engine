#include "Dac.hpp"
#include "../gfx/object.hpp"
#include "../gfx/point.hpp"
#include "../gfx/streamer.hpp"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // usleep

#include <iostream>
#include <vector>

using namespace std;

Dac::Dac(string addr) :
	address(addr),
	port(DAC::DAC_PORT_COMMS),
	dac(0),
	fd(0),
	streamer(0),
	started(false)
{
	memset(&server, 0, sizeof server);

	//fd = socket(AF_INET, SOCK_STREAM, 0);
	/*fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (fd < 0) {
		// TODO: ERROR
	}*/

	//connect();
	dac = new etherdream();
}

Dac::~Dac()
{
	// TODO
}

// TODO: This is inefficient. 
vector<DAC::dac_point> Dac::convertPoints(Points pts)
{
	vector<DAC::dac_point> newPts;

	newPts.reserve(pts.size());

	for(unsigned int i = 0; i < pts.size(); i++) {
		Point pt = pts[i];
		DAC::dac_point newPt;

		newPt.x = (int)pt.pos.x;
		newPt.y = (int)pt.pos.y;

		newPt.r = pt.color.r;
		newPt.g = pt.color.g;
		newPt.b = pt.color.b;

		newPts.push_back(newPt);
	}

	return newPts;
}


// TODO: This is inefficient. 
void Dac::convertPoints2(vector<Point> inPts, 
				etherdream_point* outPts)
{
	for(unsigned int i = 0; i < inPts.size(); i++) {
		Point pt = inPts[i];

		outPts[i].x = (int)pt.pos.x;
		outPts[i].y = (int)pt.pos.y;

		outPts[i].r = pt.color.r;
		outPts[i].g = pt.color.g;
		outPts[i].b = pt.color.b;
	}
}


void Dac::connect()
{
	/*int r = 0;
	DAC::dac_response rsp;

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

	cout << "Checking response..." << endl;
	checkResponse('?');*/

	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	
	cout << "calling etherdream_lib_start..."<<endl;

	etherdream_lib_start();
	
	usleep(1000000);

	int num = etherdream_dac_count();
	cout << "NUM DACS = " << num << endl;
	for(unsigned int i = 0; i < num; i++) {
		cout << "For loop(" << i << ")" << endl;
		int x = etherdream_get_id(etherdream_get(i));
		cout << "ed: " << x << endl;
	}

	dac = etherdream_get(0);

	cout << "TEST OMFG" << endl;

	cout << "dac.f_b_r " << dac->frame_buffer_read << endl;
	cout << "dac.f_b_f " << dac->frame_buffer_fullness << endl;

	char ipstr[INET_ADDRSTRLEN];
	cout << inet_ntop(AF_INET, &dac->addr, 
			ipstr, sizeof ipstr);

	cout << endl;

	cout << "etherdream_get worked" << endl;
	cout << "trying etherdream_connect..." << endl;

	if(etherdream_connect(dac) < 0) {
		// TODO: error
	}

	cout << "etherdream_connect worked" << endl;
}

bool Dac::prepare()
{
	DAC::prepare_command cmd; // TODO: Could be constant
	DAC::dac_response rsp;

	cout << "[dac] preparing..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('p');
}

bool Dac::begin()
{
	DAC::begin_command cmd; // TODO: Could be constant
	DAC::dac_response rsp;

	cout << "[dac] beginning..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('b');
}

bool Dac::stop()
{
	DAC::stop_command cmd; // TODO: Could be constant
	DAC::dac_response rsp;

	cout << "[dac] stopping..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('s');
}

bool Dac::clear_estop()
{
	DAC::clear_estop_command cmd; // TODO: Could be constant
	DAC::dac_response rsp;

	cout << "[dac] clearing e-stop..." << endl;

	// Messy serialization
	vector<uint8_t> cmdBuf;
	cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('d');
}

// TODO: Fix messiness
bool Dac::test_send_data(vector<DAC::dac_point> pts)
{
	DAC::data_command cmd;

	cmd.set_points(pts);
	vector<uint8_t> cmdBuf = cmd.serialize();

	send(fd, &cmdBuf[0], cmdBuf.size(), 0);
	return checkResponse('d');
}

bool Dac::checkResponse(char command) 
{
	DAC::dac_response rsp;
	vector<uint8_t> cmdBuf(22, 0);

	recv(fd, &cmdBuf[0], cmdBuf.size(), 0);

	rsp.setFromBuffer(cmdBuf);

	lastStatus = rsp.status;

	/*if(rsp.isAck()) {
		cout << "Command acknowledged (";
		cout << rsp.command << ")" << endl;
	}*/

	if(!rsp.isAck() || command != rsp.command) {
		cerr << "[!] Could not do whatever: " << command << endl;
		//rsp.print();
		return false;
	}
	else {
		cout << "COULD " << command << endl;
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

	// Only need to prepare if not already prepared
	// If then can't prepare, perhaps the last run has 
	// it confused, so try a shutdown / state refresh.
	/*if(lastStatus.playback_state == 0) {
		if(!prepare()) { 
			cerr << "DAC: FIRST 'PREPARE' NOT ACKNOWLEDGED!" << endl;
			if(!clear_estop()) {
				// TODO: Raise critical exception
				cerr << "DAC: COULD NOT CLEAR ESTOP!" << endl;
				return;
			}
			stop();
			if(!prepare()) {
				// TODO: Raise critical exception
				cerr << "DAC: 'PREPARE' NOT ACKNOWLEDGED!" << endl;
				return;
			}
		}
	}

	// TODO: Idea [!]
	// do a connect(), restart(), etc. functions that run through
	// all the commands necessary for a healthy connection

	started = false;

	unsigned int send = 1000;
	unsigned int guessRate = DEFAULT_POINTS_PER_SEND;

	while(true) 
	{
		vector<DAC::dac_point> points;

		// XXX: Not a perfect heuristic
		// Send based on buffer fullness, as some fraction of 30kpps
		guessRate = 200; // streamer->getRecommendedSendRate();
		send = (int)(guessRate * 
				(lastStatus.buffer_fullness/30000.0f));

		if(send < 200) {
			//usleep(1000);
			//waitCount++;
			//continue;
		}

		//send = 5000;

		if(send < 1) {
			cout << "SEND ZERO? (" << send << ") I THINK NOT!" << endl;
			cout << "buff: " << lastStatus.buffer_fullness << endl;
			send = 1000;
		}

		// Sometimes we can flood the DAC
		//if(started && lastStatus.buffer_fullness == 0) {
		if(started && lastStatus.isDacFlooded()) {
			cout << "**FLOOD**" << endl;
			refreshStream();
		}

		points = convertPoints(streamer->getPoints2(send));

		// FIXME: These functions and their names suck.
		if(!test_send_data(points)) {
			cout << "Tried to send " << points.size() << endl;
		}
		usleep(10000);

		if(!started) {
			started = true;
			begin();
		}
	}*/

	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	

	// Should be big enough of a vector
	etherdream_point ptBuffer[20000];

	while(1) 
	{
		Points pts = streamer->getPoints2(300);

		convertPoints2(pts, ptBuffer);

		// Writes frames...
		int nRepeat = 1; // try 1 and -1, read DOCs
		int res = etherdream_write(
				dac, 
				ptBuffer,	
				pts.size(), 
				30000, 
				nRepeat
		);

		if(res != 0) {
			cout << "Write " << res << endl;
		}

		etherdream_wait_for_ready(dac);
	}

}

void Dac::refreshStream()
{
	prepare();
	started = false;
}

