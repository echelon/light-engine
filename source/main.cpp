#include <cstdlib>
#include <iostream>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "find.hpp"
#include "Dac.hpp"

using namespace std;

int main()
{
	string ip;
	string r;

	ip = find_dac();

	Dac dac = Dac(ip);

	//cout << "Dac is: " << dac.address << endl;

	dac.connect();

	cout << "Last Status: ";
	cout << dac.lastStatus.playback_state << endl;
	dac.lastStatus.print();

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

	dac.begin();

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

	while(false) {
		int cap = 1799 - dac.lastStatus.buffer_fullness;

		cout << "Send #points: " << cap << endl;

		dac.test_send_data(cap);

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
