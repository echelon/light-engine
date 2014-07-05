#include "Dac.hpp"
#include "StreamingPointBuffer.hpp"
#include "../gfx/object.hpp"
#include "../gfx/point.hpp"
#include "../gfx/streamer.hpp"
#include "../network/ip_address.hpp"
#include "../network/mac_address.hpp"
#include "../network/exceptions.hpp"
#include "../pipeline/Frame.hpp"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // usleep

#include <iostream>
#include <vector>

using namespace std;
using namespace LE;

Network::IpAddress Dac::find_broadcast_ip_with_mac(
	const Network::MacAddress& macAddress) {
  int fd = 0; 
  int r = 0;
  char buf[1024];
  char ipstr[INET_ADDRSTRLEN];

  sockaddr_in client; 
  sockaddr_in sender;
  socklen_t sendsize = sizeof sender;

  memset(&sender, 0, sizeof sender);
  memset(&client, 0, sizeof client);
  memset(&buf, 0, sizeof buf);

  client.sin_family = AF_INET;
  client.sin_port = htons(DAC_PORT_BCAST);
  client.sin_addr.s_addr = INADDR_ANY;

  fd = socket(AF_INET, SOCK_DGRAM, 0);
	
  if (fd < 0) {
	throw Network::SocketException("Could not create socket.");
  }

  r = ::bind(fd, (sockaddr*)&client, sizeof(client));

  if (r < 0) {
	throw Network::SocketException("Could not bind port.");
  }

  Network::IpAddress ip;

  while (1) {
	recvfrom(fd, buf, sizeof buf, 0, (sockaddr*)&sender, &sendsize);
	string ipStr = inet_ntop(AF_INET, &sender.sin_addr, ipstr, 
		sizeof ipstr);

	if (ipStr.size() < 7) {
	  continue;
	}

	ip = Network::IpAddress(ipStr);

	// Ping IP and then look up in ARP table
	Network::MacAddress mac = 
	  Network::MacAddress::lookup_from_ip_with_arp_table(ip, true);

	if (macAddress != mac) {
	  continue;
	}
	break;
  }

  return ip;
}

Dac::Dac(const string& addr) :
  ipAddress(Network::IpAddress(addr)),
  address(ipAddress.toString()),
  port(DAC_PORT_COMMS),
  fd(0),
  streamer(0),
  started(false)
{
  memset(&server, 0, sizeof server);

  //fd = socket(AF_INET, SOCK_STREAM, 0);
  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  if (fd < 0) {
	// TODO: ERROR
  }

  //connect();
}

Dac::Dac(const Network::IpAddress& ipAddr) :
  ipAddress(ipAddr),
  address(ipAddr.toString()),
  port(DAC_PORT_COMMS),
  fd(0),
  streamer(0),
  started(false)
{
  memset(&server, 0, sizeof server);

  //fd = socket(AF_INET, SOCK_STREAM, 0);
  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  if (fd < 0) {
	// TODO: ERROR
  }

  //connect();
}

Dac::~Dac()
{
  // TODO
}

// TODO: This is inefficient. 
shared_ptr<vector<dac_point>> Dac::convertPoints(shared_ptr<Points> pts)
{
  vector<dac_point>* newPts = new vector<dac_point>;
  vector<dac_point>& newPtsRef = *newPts;

  Points& ptsRef = *pts;

  newPts->reserve(pts->size());

  for (unsigned int i = 0; i < ptsRef.size(); i++) {
	Point pt =ptsRef[i];
	dac_point newPt;

	newPt.x = (int)pt.pos.x;
	newPt.y = (int)pt.pos.y;

	//cout << pt.pos.x << "." << pt.pos.y << endl;
	//cout << newPt.x << ":" << newPt.y << endl;

	newPt.r = pt.color.r;
	newPt.g = pt.color.g;
	newPt.b = pt.color.b;

	newPtsRef.push_back(newPt);

	/*int k = 1;
	while(k) {
	  // XXX: Just an experiment to waste CPU cycles
	  for(unsigned int j = 0; j < newPtsRef.size(); j++) {
		pt.x = newPt.x;
		pt.y = newPt.y;
		pt.r = newPt.r;
		pt.g = newPt.g;
		pt.b = newPt.b;
	  }
	  k--;
	}*/
  }

  return shared_ptr<vector<dac_point>>(newPts);
}

// TODO: This is inefficient. 
shared_ptr<vector<dac_point>> Dac::convertPoints(
	shared_ptr<Points> trackInPts, shared_ptr<Points> pts)
{
  vector<dac_point>* newPts = new vector<dac_point>;
  vector<dac_point>& newPtsRef = *newPts;

  Points& trackPtsRef = *trackInPts;
  Points& ptsRef = *pts;

  newPts->reserve(trackInPts->size() + pts->size());

  for (unsigned int i = 0; i < trackPtsRef.size(); i++) {
	Point pt = trackPtsRef[i];
	dac_point newPt;

	newPt.x = (int)pt.pos.x;
	newPt.y = (int)pt.pos.y;
	newPt.r = pt.color.r;
	newPt.g = pt.color.g;
	newPt.b = pt.color.b;

	newPtsRef.push_back(newPt);
  }

  for (unsigned int i = 0; i < ptsRef.size(); i++) {
	Point pt =ptsRef[i];
	dac_point newPt;

	newPt.x = (int)pt.pos.x;
	newPt.y = (int)pt.pos.y;

	newPt.r = pt.color.r;
	newPt.g = pt.color.g;
	newPt.b = pt.color.b;

	newPtsRef.push_back(newPt);
  }

  return shared_ptr<vector<dac_point>>(newPts);
}

void Dac::connect()
{
  int r = 0;
  dac_response rsp;

  cout << "[dac] connecting... (" << address << ")" << endl;

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(address.c_str());
  server.sin_port = htons(port);

  r = ::connect(fd, (sockaddr*)&server, sizeof server);

  if (r < 0) {
	// TODO ERROR
	cerr << "Could not connect() to DAC!" << endl;
	return;
  }

  checkResponse('?');
}

bool Dac::prepare()
{
  prepare_command cmd; // TODO: Could be constant
  dac_response rsp;

  //cout << "[dac] preparing..." << endl;

  // Messy serialization
  vector<uint8_t> cmdBuf;
  cmdBuf = cmd.serialize();

  send(fd, &cmdBuf[0], cmdBuf.size(), 0);
  return checkResponse('p');
}

bool Dac::begin()
{
  begin_command cmd; // TODO: Could be constant
  dac_response rsp;

  cout << "[dac] beginning..." << endl;

  // Messy serialization
  vector<uint8_t> cmdBuf;
  cmdBuf = cmd.serialize();

  send(fd, &cmdBuf[0], cmdBuf.size(), 0);
  return checkResponse('b');
}

bool Dac::stop()
{
  stop_command cmd; // TODO: Could be constant
  dac_response rsp;

  cout << "[dac] stopping..." << endl;

  // Messy serialization
  vector<uint8_t> cmdBuf;
  cmdBuf = cmd.serialize();

  send(fd, &cmdBuf[0], cmdBuf.size(), 0);
  return checkResponse('s');
}

bool Dac::clear_estop()
{
  clear_estop_command cmd; // TODO: Could be constant
  dac_response rsp;

  cout << "[dac] clearing e-stop..." << endl;

  // Messy serialization
  vector<uint8_t> cmdBuf;
  cmdBuf = cmd.serialize();

  send(fd, &cmdBuf[0], cmdBuf.size(), 0);
  return checkResponse('d');
}

// TODO: Fix messiness
// TODO: Rename. WTF is it named this?
bool Dac::test_send_data(unique_ptr<vector<dac_point>> pts) {
  data_command cmd;

  /*cout << "Sending " 
	<< pts->size() 
	<< " encoded points to DAC over the wire" << endl;*/

  cmd.set_points(*pts);
  vector<uint8_t> cmdBuf = cmd.serialize();

  send(fd, &cmdBuf[0], cmdBuf.size(), 0);
  return checkResponse('d');
}

bool Dac::checkResponse(char command) {
  dac_response rsp;
  vector<uint8_t> cmdBuf(22, 0);

  recv(fd, &cmdBuf[0], cmdBuf.size(), 0);

  rsp.setFromBuffer(cmdBuf);

  lastStatus = rsp.status;

  /*if(rsp.isAck()) {
	  cout << "Command acknowledged (";
	  cout << rsp.command << ")" << endl;
  }*/

  if(!rsp.isAck() || command != rsp.command) {
	//cerr << "[!] Could not do whatever: " << command << endl;
	//rsp.print();
	return false;
  }

  return true;
}

void Dac::setStreamer(Streamer* s)
{
	streamer = s;
}

void Dac::stream()
{
  /*// TODO: Check if connected. 
  connect();

  // Only need to prepare if not already prepared
  // If then can't prepare, perhaps the last run has 
  // it confused, so try a shutdown / state refresh.
  if(lastStatus.playback_state == 0) {
	if(!prepare()) { 
	  cerr << "DAC: FIRST 'PREPARE' NOT ACKNOWLEDGED!" << endl;
	  if(!clear_estop()) {
		// TODO: Raise critical exception
		cerr << "DAC: COULD NOT CLEAR ESTOP!" << endl;
		return;
	  }
	  stop();
	  if(!prepare()) {
		// TODO: Raise critical exception
		cerr << "DAC: 'PREPARE' NOT ACKNOWLEDGED!" << endl;
		return;
	  }
	}
  }

  // TODO: Idea [!]
  // do a connect(), restart(), etc. functions that run through
  // all the commands necessary for a healthy connection

  started = false;

  unsigned int send = 1000;
  unsigned int guessRate = DEFAULT_POINTS_PER_SEND;

  while (true) {
	vector<dac_point> points;

	// XXX: Not a perfect heuristic
	// Send based on buffer fullness, as some fraction of 30kpps
	guessRate = 2000; // streamer->getRecommendedSendRate();
	send = (int)(guessRate * (lastStatus.buffer_fullness/30000.0f));

	if(send < 100) {
	  send = 1000;
	}

	// Sometimes we can flood the DAC
	//if(started && lastStatus.buffer_fullness == 0) {
	if(started && lastStatus.isDacFlooded()) {
	  refreshStream();
	}

	points = convertPoints(streamer->getPoints2(send));

	// FIXME: These functions and their names suck.
	if(!test_send_data(points)) {
	  //cout << "Tried to send " << points.size() << endl;
	}
	usleep(10000);

	if(!started) {
	  started = true;
	  begin();
	}
  }*/
}

void Dac::refreshStream()
{
  prepare();
  started = false;
}


void Dac::setFrameBuffer(shared_ptr<LE::FrameBuffers> buffer) {
  frameBuffer = buffer;
}

void Dac::setTracking(shared_ptr<LE::Tracking> t) {
  tracking = t;
}

void Dac::streamFrameBuffer() 
{
  // TODO: Check if connected. 
  connect();

  // Only need to prepare if not already prepared
  // If then can't prepare, perhaps the last run has 
  // it confused, so try a shutdown / state refresh.
  if(lastStatus.playback_state == 0) {
	if(!prepare()) { 
	  cerr << "DAC: FIRST 'PREPARE' NOT ACKNOWLEDGED!" << endl;
	  if(!clear_estop()) {
		// TODO: Raise critical exception
		cerr << "DAC: COULD NOT CLEAR ESTOP!" << endl;
		return;
	  }
	  stop();
	  if(!prepare()) {
		// TODO: Raise critical exception
		cerr << "DAC: 'PREPARE' NOT ACKNOWLEDGED!" << endl;
		return;
	  }
	}
  }

  // TODO: Idea [!]
  // do a connect(), restart(), etc. functions that run through
  // all the commands necessary for a healthy connection

  started = false;

  unsigned int send = 1000;
  unsigned int guessRate = DEFAULT_POINTS_PER_SEND;

  StreamingPointBuffer streamBuffer;

  // For tracking
  Point curPoint;
  Point lastPoint;

  while (true) {
	// XXX: Not a perfect heuristic
	// Send based on buffer fullness, as some fraction of 30kpps
	guessRate = 2000;
	send = (int)(guessRate * (lastStatus.buffer_fullness/30000.0f));
	if (send < 100) {
	  send = 1000;
	}

	// Sometimes we can flood the DAC
	// if(started && lastStatus.buffer_fullness == 0) {
	if (started && lastStatus.isDacFlooded()) {
	  refreshStream();
	}

	// Only request a new frame when we're out of points to send.
	// We stream from the buffer, not directly from the frame!
	while (streamBuffer.size() < send) {
	  shared_ptr<Frame> curFrame = frameBuffer->getLasingFrame();
	  shared_ptr<Points> framePts;

	  // Keep swapping frame until we get one with points. 
	  // (Should only occur at init.)
	  do {
		frameBuffer->doneLasing(); // performs buffer swap (TODO: confirm)
		curFrame = frameBuffer->getLasingFrame();
	  } while (!curFrame->hasPoints());

	  // TODO: This sucks...
	  Points pts = curFrame->copyPoints();
	  framePts = shared_ptr<Points>(new Points(pts));

	  curFrame->markGotPoints();

	  lastPoint = curPoint;
	  curPoint = framePts->back();

	  /*cout << "Last Point - x: " 
		<< lastPoint.pos.x 
		<< " y: " 
		<< lastPoint.pos.y
		<< endl;

	  cout << "Curr Point - x: " 
		<< curPoint.pos.x 
		<< " y: " 
		<< curPoint.pos.y
		<< endl;*/

	  shared_ptr<Points> trackPts = 
		tracking->track(lastPoint, curPoint);

	  streamBuffer.add(convertPoints(trackPts, framePts));

	  // Now safe to deallocate framePoints ptr
	  frameBuffer->doneLasing(); // TODO: Before or after?
	}

	//auto before = streamBuffer.size();

	// We don't send large messages (~1000 points)
	unique_ptr<vector<dac_point>> packetPoints = streamBuffer.get(send);

	//auto after = streamBuffer.size();

	/*cout << "Stream buffer size before get(): " 
	  << before 
	  << " after: "
	  << after
	  << " got these to send: "
	  << packetPoints->size()
	  << endl;*/

	// FIXME: These functions and their names suck.
	if(!test_send_data(move(packetPoints))) {
	  //cout << "Tried to send " << points.size() << endl;
	}

	usleep(10000);

	if(!started) {
	  started = true;
	  begin();
	}
  }
}
