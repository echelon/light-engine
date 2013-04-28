#include <cstdlib>
#include <iostream>
#include <vector>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "find.hpp"
#include "types.hpp"
#include "commands.hpp"
#include "Dac.hpp"

using namespace std;

vector<dac_point> makePoints(unsigned int num) 
{
	vector<dac_point> points;
	dac_point pt;

	for(unsigned int i = 0; i < num; i++) {
		pt.x = 0;
		pt.y = 0;
		pt.r = CMAX;
		pt.g = CMAX;
		pt.b = CMAX;
		points.push_back(pt);
	}

	return points;
}

int main()
{
	string ip;
	string r;

	ip = find_dac();

	Dac dac = Dac(ip);

	//cout << "Dac is: " << dac.address << endl;

	dac.connect();

	// If can't prepare, perhaps the last run has it confused.
	// Try to stop...
	if(!dac.prepare()) { 
		// Clear any existing state!
		if(!dac.clear_estop()) {
			return EXIT_FAILURE; 
		}

		dac.stop();
		if(!dac.prepare()) {
			return EXIT_FAILURE; 
		}
	}

	//dac.begin();

	/*switch(dac.lastStatus.playback_state) {
		case 2:
			cout << "DAC.lastStatus = 2" << endl;
			cout << endl;
			return EXIT_FAILURE;
			break;
		case 0:
			cout << "DAC.lastStatus = 0" << endl;
			cout << endl;
			
			// If can't prepare, perhaps the last run has it confused.
			// Try to stop...
			if(!dac.prepare()) { 
			// Stop any existing state!
				if(!dac.clear_estop()) {
					return EXIT_FAILURE; 
				}

				dac.stop();
				if(!dac.prepare()) {
					return EXIT_FAILURE; 
				}
			}
			break;
	}*/

	bool started = false;

	//cout << endl << endl;

	vector<dac_point> points;

	//for(unsigned int i = 0; i < 10; i++) 
	while(true)
	{
		int npoints = 1799 - dac.lastStatus.buffer_fullness;
		if(npoints < 20) {
			npoints = 1799;
		}

		//npoints = 2;

		cout << "Send #points: " << npoints << endl;

		points = makePoints(npoints);
		dac.test_send_data(points);

		if(!started) {
			started = true;
			dac.begin();
		}
	}

	// Receive '?'
	/*r = dac.read(2);
	cout << r << endl;

	// Send 'p'
	cout << "Sending 'p'" << endl;
	//dac->prepare();
	r = dac.read(2);
	cout << r << endl;

	dac->prepare();
	r = dac->read(22);
	cout << r << endl;*/

	/*cout << "Test send... 1" << endl;
	dac->send();

	cout << "Test send... 2" << endl;
	dac->send();

	cout << "Test send... 3" << endl;
	dac->send();*/

	return EXIT_SUCCESS;
}
