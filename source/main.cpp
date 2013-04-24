#include <cstdlib>
#include <iostream>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Dac.hpp"

using namespace std;

int main()
{
	string ip;
	string r;

	ip = find_dac();

	Dac dac = Dac(ip);

	cout << "Dac is: " << dac.address << endl;

	dac.connect();
 
	// Stop any existing state!
	if(!dac.clear_estop()) {
		return EXIT_FAILURE; 
	}
	if(!dac.prepare()) { return EXIT_FAILURE; }
	//if(!dac.begin()) { return EXIT_FAILURE; }

	bool started = false;
	while(true) {
		dac.test_send_data();
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
