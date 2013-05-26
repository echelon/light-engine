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
#include "gfx/surface.hpp"
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

Surface surface (20000, 20000, -20000, 0);
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
	Dac dac = Dac(find_dac());
	dac.setStreamer(streamer);
	dac.stream();
}

// Random magnitude
int rsign() {
	if(uniform_int_distribution<>(0, 1)(randgen) == 1) {
		return 1;
	}
	return -1;
}

int main()
{
	const unsigned int NUM = 7;
    uniform_int_distribution<> vel(1, 10);
    uniform_int_distribution<> scale(1, 3);

	streamer->setSurface(surface);

	for(unsigned int i = 0; i < NUM; i++) {
		Object* o = new Circle(40);
		Entity* e = new Entity();

		o->setColor(WHITE);
		if(i%2 == 0) {
			o->setColor(GREEN);
		}
		o->setScale((float)scale(randgen)/10 * 0.5);

		e->setSurfaceAsBoundary(surface);
		e->setVelocity(vel(randgen)*rsign(), vel(randgen)*rsign());

		streamer->addObject(o);
		objects.push_back(o);
		entities.push_back(e);
	}

	thread dt(dac_thread);
	thread mt(move_thread);

	dt.join();
	mt.join();

	return EXIT_SUCCESS;
}
