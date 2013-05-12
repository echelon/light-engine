#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <random>

#include "misc.hpp" // XXX TEMP
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <unistd.h> // usleep

#include "etherdream/find.hpp"
#include "etherdream/types.hpp"
#include "etherdream/commands.hpp"
#include "etherdream/Dac.hpp"
#include "gfx/streamer.hpp"
#include "gfx/color.hpp"
#include "asset/circle.hpp"
#include "game/entity.hpp"

using namespace std;

vector<Circle*> circles;
vector<Entity*> entities;

//Circle* circle1 = new Circle(20000.0f, 100);
//Circle* circle2 = new Circle(1000.0f, 100);

Streamer* streamer = new Streamer();

random_device rd;
mt19937 randgen(rd());
 
void move_thread() 
{
	while(true) {
		for(unsigned int i = 0; i < entities.size(); ++i) {
			Entity* e = entities[i];
			Circle* c = circles[i];

			e->tickVelocity();

			c->setX(e->getX());
			c->setY(e->getY());
		}

		usleep(1000);
	}
}

void dac_thread() 
{
	string ip;

	ip = find_dac();

	Dac dac = Dac(ip);
	dac.setStreamer(streamer);
	dac.stream();
}

int main()
{
	const unsigned int NUM = 5;
   	uniform_int_distribution<> pos(-200, 200);
    uniform_int_distribution<> vel(-15, 15);

	for(unsigned int i = 0; i < NUM; i++) {
		Circle* c = new Circle(2000.f * ((i%3)+1), 120);
		Entity* e = new Entity();

		circles.push_back(c);
		entities.push_back(e);

		streamer->addObject(c);

		e->setBoundary(20000);
		e->setVelocity(vel(randgen), vel(randgen));
		e->setPosition(pos(randgen), pos(randgen));

		switch(i % 3) {
			case 0:
				c->setColor(0, 0, CMAX);
				break;
			case 1:
				c->setColor(0, CMAX, 0);
				break;
			case 2:
				c->setColor(CMAX, CMAX, CMAX);
				break;
			default:
				c->setColor(CMAX, CMAX, CMAX);
				break;
		}
	}

	thread dt(dac_thread);
	thread mt(move_thread);

	dt.join();
	mt.join();

	return EXIT_SUCCESS;
}
