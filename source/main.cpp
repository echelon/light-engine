#include <cstdlib>
#include <iostream>
#include <vector>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

#include "etherdream/find.hpp"
#include "etherdream/types.hpp"
#include "etherdream/commands.hpp"
#include "etherdream/Dac.hpp"
#include "gfx/streamer.hpp"
#include "asset/circle.hpp"

using namespace std;

vector<Circle*> circles;

//Circle* circle1 = new Circle(20000.0f, 100);
//Circle* circle2 = new Circle(1000.0f, 100);

Streamer* streamer = new Streamer();

int main()
{
	string ip;
	string r;

	ip = find_dac();

	Dac dac = Dac(ip);

	for(unsigned int i = 0; i < 10; i++) {
		Circle* c = new Circle(1000.f * (i+1), 2000);
		circles.push_back(c);
		streamer->addObject(c);
	}
	//cout << "Dac is: " << dac.address << endl;

	dac.setStreamer(streamer);
	dac.stream();

	return EXIT_SUCCESS;
}
