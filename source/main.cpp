#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <memory>
#include <chrono>

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

#include "pipeline/Tracking.hpp"
#include "pipeline/Geometry.hpp"
#include "pipeline/FourMatrix.hpp"
#include "pipeline/FrameBuffers.hpp"
#include "pipeline/Frame.hpp"
#include "pipeline/MatrixStack.hpp"

using namespace std;
using namespace LE;

const Network::MacAddress MAC_A("00:04:A3:87:28:CD");
const Network::MacAddress MAC_B("00:04:A3:3D:0B:60");

// Configure the projector to talk to by default
const Network::MacAddress USE_MAC = MAC_A;

shared_ptr<LE::FrameBuffers> FRAME_BUFFERS(new LE::FrameBuffers);
shared_ptr<LE::Tracking> TRACKING(new LE::Tracking);

random_device rd;
mt19937 randgen(rd());

// On demand 1 or -1
int random_sign() {
  if(uniform_int_distribution<>(0, 1)(randgen) == 1) {
	return 1;
  }
  return -1;
}

float x = 0;
float y = 0;
int mag = 1;

void animation_thread() {
  int MAX = 10000;
  int MIN = -10000;

  auto start = std::chrono::system_clock::now();
  auto finish = std::chrono::system_clock::now();

  while (true) {
	auto elapsed = finish - start;
	start = std::chrono::system_clock::now();

	float add = elapsed.count() / 100.0f;

	//cout << "Elapsed: " << add << endl;
	//cout << "x: " << x << ", y: " << y << endl;

	if (x >= MAX) {
	  mag *= -1;
	}
	else if (y <= MIN) {
	  mag *= -1;
	}

	x += add * mag;
	y += add * mag;

	finish = std::chrono::system_clock::now();
  }
}

LE::Geometry make_circle(unsigned int radius, 
	unsigned int sample_points) {
  Points pts;

  for (unsigned int i = 0; i < sample_points; i++) {
	float s = (float)i / sample_points * 2 * M_PI;
	float x = cos(s) * radius;
	float y = sin(s) * radius;
	pts.push_back(Point(x, y));
	//cout << x << "," << y << endl;
  }

  return LE::Geometry(pts);
}

void draw_thread() {
  LE::Geometry circle = make_circle(5000, 50000);
  MatrixStack matStack;

  while (true) {
	shared_ptr<Frame> drawing = FRAME_BUFFERS->getDrawingFrame();
	drawing->beginDrawing();

	// TODO: This will be wrapped up in the higher-level entity system

	matStack.push(FourMatrix::translation(0, 5000, 1.0f));
	//drawing->draw(circle, matStack);
	drawing->draw(circle);
	matStack.pop();

	drawing->finishDrawing();
	FRAME_BUFFERS->doneDrawing();
	//FRAME_BUFFERS->printFullStats();
  }
}

void laser_thread() {
  Network::IpAddress ipAddress = Dac::find_broadcast_ip_with_mac(USE_MAC);
  Dac dac = Dac(ipAddress);

  dac.setFrameBuffer(FRAME_BUFFERS);
  dac.setTracking(TRACKING);
  dac.streamFrameBuffer();
}

int main() {
  thread animating(animation_thread);
  thread drawing(draw_thread);
  thread lasing(laser_thread);

  animating.join();
  drawing.join();
  lasing.join();

  return EXIT_SUCCESS;
}

