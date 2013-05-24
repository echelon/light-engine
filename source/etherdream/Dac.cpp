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

Dac::Dac() :
	dac(0),
	streamer(0)
{
	dac = new etherdream();
}

Dac::~Dac()
{
	// TODO
}

void Dac::connect()
{
	etherdream_lib_start();
	
	// Wait to find DACs (how libetherdream works)
	usleep(1000000);

	unsigned int num = etherdream_dac_count();

	// TODO: Necessary? 
	for(unsigned int i = 0; i < num; i++) {
		etherdream_get_id(etherdream_get(i));
	}

	dac = etherdream_get(0);

	// IP Address of DAC
	char ipstr[INET_ADDRSTRLEN];
	cout << inet_ntop(AF_INET, &dac->addr, 
			ipstr, sizeof ipstr) << endl;

	if(etherdream_connect(dac) < 0) {
		// TODO: error
	}
}

void Dac::setStreamer(Streamer* s)
{
	streamer = s;
}

void Dac::stream()
{
	// TODO: Check if connected. 
	connect();

	// Should be big enough of a vector
	etherdream_point ptBuffer[20000];

	while(1) 
	{
		Points pts = streamer->getPoints2(300);

		convertPoints(pts, ptBuffer);

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

// TODO: This is inefficient. 
void Dac::convertPoints(Points inPts, 
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

