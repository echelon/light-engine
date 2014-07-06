#include <vector>
#include <thread>
#include <memory>
#include <iostream>
#include <cstdlib>

#include "network/ip_address.hpp"
#include "network/mac_address.hpp"

#include "etherdream/types.hpp"
#include "etherdream/commands.hpp"
#include "etherdream/Dac.hpp"

#include "pipeline/Tracking.hpp"
#include "pipeline/SimpleTracking.hpp"
#include "pipeline/Geometry.hpp"
#include "pipeline/FourMatrix.hpp"
#include "pipeline/FrameBuffers.hpp"
#include "pipeline/Frame.hpp"
#include "pipeline/MatrixStack.hpp"

#include "gfx/color.hpp"
#include "tools/BounceAnimation.hpp"

// TODO: Build facilities for stats on draw framerate and play (lase) framerate!

// TODO: Make an ILDA-file format player that works on this system. 
// Probably the next immediate goal, and will validate my direction.

// XXX/NOTE: Artifacts are probably just absense of blanking!

using namespace std;
using namespace LE;

const Network::MacAddress MAC_A("00:04:A3:87:28:CD");
const Network::MacAddress MAC_B("00:04:A3:3D:0B:60");

// Configure the projector to talk to by default
const Network::MacAddress USE_MAC = MAC_A;

shared_ptr<Tracking> TRACKING(new SimpleTracking(15, 40, GREEN, RED));
shared_ptr<FrameBuffers> FRAME_BUFFERS(new FrameBuffers);

BounceAnimation ANIMATION(5);

Geometry make_circle(unsigned int radius, 
	unsigned int sample_points) {
  Points pts;

  for (unsigned int i = 0; i < sample_points; i++) {
	float s = (float)i / sample_points * 2 * M_PI;
	float x = cos(s) * radius;
	float y = sin(s) * radius;
	pts.push_back(Point(x, y));
  }
  return Geometry(pts);
}

/** 
 * Draw object with matrix stack, then pop the top. 
 * Convenience method. Very not threadsafe.
 */
void draw_and_pop(shared_ptr<Frame> drawing, Geometry& geo, 
	MatrixStack& matStack) {
  drawing->draw(geo, matStack);
  matStack.pop();
}

void draw_thread() {
  Geometry circle = make_circle(5000, 50);
  MatrixStack matStack;

  while (true) {
	shared_ptr<Frame> drawing = FRAME_BUFFERS->getDrawingFrame();
	drawing->beginDrawing();

	unique_ptr<Positions> positions = ANIMATION.getPositionsUnique();
	for (Position p : *positions) {
	  matStack.push(FourMatrix::translation(p.x, p.y, 1.0f));
	  draw_and_pop(drawing, circle, matStack);
	}

	drawing->finishDrawing();
	FRAME_BUFFERS->doneDrawing();
	//FRAME_BUFFERS->printFullStats();
	ANIMATION.randomizePositions();
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
  FRAME_BUFFERS->setTracking(TRACKING);

  ANIMATION.setBoundaries(25000.0f, -25000.0f, 0.0f, 0.0f);
  ANIMATION.setVelocityMagnitudes(25.0f, 50.0f);
  ANIMATION.pause();
  ANIMATION.start();

  thread drawing(draw_thread);
  thread lasing(laser_thread);

  drawing.join();
  lasing.join();

  return EXIT_SUCCESS;
}

