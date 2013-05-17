#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <random>

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
#include "asset/square.hpp"
#include "game/entity.hpp"

using namespace std;

vector<Object*> objects;
vector<Entity*> entities;

Streamer* streamer = new Streamer();

random_device rd;
mt19937 randgen(rd());
 
void move_thread() 
{
	while(true) {
		for(unsigned int i = 0; i < entities.size(); ++i) {
			Entity* e = entities[i];
			Object* c = objects[i];

			e->tickVelocity();
			c->setPosition(e->getPosition());
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
	const unsigned int NUM = 7;
   	uniform_int_distribution<> pos(-200, 200);
    uniform_int_distribution<> vel(-15, 15);

	for(unsigned int i = 0; i < NUM; i++) {
		Object* o = 0;
		Entity* e = new Entity();

		switch(uniform_int_distribution<>(0, 1)(randgen)) {
			case 0:
				o = new Circle(); //2000.f * ((i%3)+1), 120);
				break;
			case 1:
			default:
				//o = new Square(); //2000.f);
				o = new Circle();
		}

		objects.push_back(o);
		entities.push_back(e);

		streamer->addObject(o);

		e->setBoundary(20000);
		e->setVelocity(vel(randgen), vel(randgen));
		e->setPosition(pos(randgen), pos(randgen));

		switch(uniform_int_distribution<>(0, 2)(randgen)) {
			case 0:
				o->setColor(0, 0, CMAX);
				break;
			case 1:
				o->setColor(0, CMAX, 0);
				break;
			case 2:
			default:
				o->setColor(CMAX, CMAX, CMAX);
				break;
		}
	}

	thread dt(dac_thread);
	thread mt(move_thread);

	dt.join();
	mt.join();

	return EXIT_SUCCESS;
}
