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

Circle* circle1 = new Circle(20000.0f, 100);
//Circle* circle2 = new Circle(20000.0f, 100);
Streamer* streamer = new Streamer();

int main()
{
	string ip;
	string r;

	ip = find_dac();

	Dac dac = Dac(ip);

	//cout << "Dac is: " << dac.address << endl;

	streamer->addObject(circle1);
	//streamer->addObject(circle2);

	dac.setStreamer(streamer);
	dac.stream();

	return EXIT_SUCCESS;
}
