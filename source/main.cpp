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
#include "gfx/illuminator.hpp"
#include "asset/circle.hpp"
#include "asset/square.hpp"
#include "asset/illum/solid.hpp"
#include "asset/illum/blink.hpp"
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
	const unsigned int NUM = 1;
   	uniform_int_distribution<> pos(-200, 200);
    uniform_int_distribution<> vel(-15, 15);
    uniform_int_distribution<> scale(4, 5);

	Colors colors;
	colors.push_back(INVISIBLE);
	//colors.push_back(GREEN);
	colors.push_back(WHITE);

	for(unsigned int i = 0; i < NUM; i++) {
		Object* o = 0;
		Entity* e = new Entity();
		Illuminator* il = 0;

		switch(uniform_int_distribution<>(0, 1)(randgen)) {
			case 0:
				o = new Circle();
				break;
			case 1:
			default:
				o = new Square();
		}

		objects.push_back(o);
		entities.push_back(e);

		streamer->addObject(o);

		switch(uniform_int_distribution<>(0, 2)(randgen)) {
			case 0:
				il = new BlinkIlluminator(*o, colors, 3);
				//o->setColor(0, 0, CMAX);
				break;
			case 1:
				il = new SolidIlluminator(*o, GREEN);
				//o->setColor(0, CMAX, 0);
				break;
			case 2:
			default:
				o->setColor(CMAX, CMAX, CMAX);
				break;
		}

		il = new BlinkIlluminator(*o, colors, 20);

		o->setIlluminator(il);
		e->setBoundary(20000);
		e->setVelocity(vel(randgen), vel(randgen));
		e->setPosition(pos(randgen), pos(randgen));
		o->setScale((float)scale(randgen)/10 * 0.5);
	}

	thread dt(dac_thread);
	thread mt(move_thread);

	dt.join();
	mt.join();

	return EXIT_SUCCESS;
}
