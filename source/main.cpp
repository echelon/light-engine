#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <memory>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <unistd.h> // usleep

#include "network/ip_address.hpp"
#include "network/mac_address.hpp"
#include "etherdream/types.hpp"
#include "etherdream/commands.hpp"
#include "etherdream/Dac.hpp"
#include "gfx/streamer.hpp"
#include "gfx/surface.hpp"
#include "gfx/color.hpp"
#include "gfx/illuminator.hpp"
#include "asset/shapes.hpp"
#include "asset/illum/solid.hpp"
#include "asset/illum/blink.hpp"
#include "game/entity.hpp"

#include "pipeline/FourMatrix.hpp"
#include "pipeline/FrameBuffers.hpp"
#include "pipeline/Frame.hpp"
#include "pipeline/MatrixStack.hpp"

using namespace std;
using namespace LE;

const Network::MacAddress MAC_A("00:04:A3:87:28:CD");
const Network::MacAddress MAC_B("00:04:A3:3D:0B:60");

vector<Object*> objects;
vector<Entity*> entities;

Surface surface (20000, 20000, -20000, 0);
Streamer* streamer = new Streamer();

random_device rd;
mt19937 randgen(rd());
 
void move_thread() {
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

void dac_thread() {
  Network::IpAddress ipAddress = Dac::find_broadcast_ip_with_mac(MAC_B);
  Dac dac = Dac(ipAddress);

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

void testing_matrices() {
  FourMatrix a = FourMatrix();
  FourMatrix b = FourMatrix::identity();
  MatrixStack stack = MatrixStack();

  a.setAt(3, 1.3f);
  a.setAt(5, 5.3f);
  a.setAt(9, 9.3f);
  a.setAt(12, 11.3f);

  b.setAt(1, 1.2f);
  b.setAt(3, -15.3f);
  b.setAt(7, 0.3f);

  cout << "Mat A: " << endl;
  cout << a.toString();
  cout << "Mat B: " << endl;
  cout << b.toString();

  FourMatrix c = a * b;

  cout << "Mat C: " << endl;
  cout << c.toString();

  stack.push(a);
  stack.push(b);

  cout << "MatStack->push(a)->push(b)->top(): " << endl;
  cout << stack.top().toString();

}


void testing_framebuffers() {

  LE::FrameBuffers buffers;

  shared_ptr<Frame> lasing;
  shared_ptr<Frame> drawing;

  for(unsigned int i = 0; i < 5; i++) {
	lasing = buffers.getLasingFrame();
	drawing = buffers.getDrawingFrame();

	cout << "Lase Read:\t" << lasing->canRead() << endl;
	cout << "Lase Write:\t" << lasing->canWrite() << endl;
	cout << "Draw Read:\t" << drawing->canRead() << endl;
	cout << "Draw Write:\t" << drawing->canWrite() << endl;

	buffers.doneDrawing();
  }
}


int main() {

  testing_matrices();
  testing_framebuffers();

  const unsigned int NUM = 7;
  uniform_int_distribution<> vel(1, 10);
  uniform_int_distribution<> scale(1, 3);

  streamer->setSurface(surface);

  for (unsigned int i = 0; i < NUM; i++) {
	//Object* o = new Circle(40);
	Object* o = new Rectangle();
	Entity* e = new Entity();

	o->setColor(WHITE);
	if (i%2 == 0) {
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

