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
#include "asset/shapes.hpp"
#include "asset/illum/solid.hpp"
#include "asset/illum/blink.hpp"
#include "game/entity.hpp"

#include "networking/mac_address.hpp"

using namespace std;

using namespace LE;
/*void dac_thread() {
  string dac = find_dac();
  cout << "Found dac: " << dac << endl;
}*/

int main() {

  Network::MacAddress mac = MacAddress::lookup_from_ip();
  //thread dt(dac_thread);
  //dt.join();
  //

  return EXIT_SUCCESS;
}

