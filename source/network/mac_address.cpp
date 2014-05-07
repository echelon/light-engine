#include "mac_address.hpp"
#include "ip_address.hpp"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h> // string comparison

using namespace std;

const int DAC_PORT_BCAST = 7654; // TEMP
const int DAC_PORT_COMMS = 7765; // TEMP

namespace LE {
  namespace Network {

	
	MacAddress MacAddress::lookup_from_ip_with_arp_table(const IpAddress& ipAddress,
		bool ping) {

	  if(!ipAddress.isValid()) {
		return MacAddress();
	  }

	  char line[500];
	  char ip_address[500];
	  int hw_type;
	  int flags;
	  char mac_address[500];
	  char mask[500];
	  char device[500];

	  MacAddress foundMac;

	  if (ping) {
		ipAddress.ping(1000);
	  }

	  // ARP Table Reading Suggestion From
	  // http://stackoverflow.com/a/21031888

	  FILE *fp = fopen("/proc/net/arp", "r");
	  fgets(line, sizeof(line), fp);    // Skip the first line (column headers).

	  while(fgets(line, sizeof(line), fp)) {
		  sscanf(line, "%s 0x%x 0x%x %s %s %s\n",
				ip_address,
				&hw_type,
				&flags,
				mac_address,
				mask,
				device);

		  if (ipAddress.toString().compare(ip_address) == 0) {
			foundMac = MacAddress(mac_address);
			break;
		  } 
	  }

	  fclose(fp);
	  return foundMac;
	}

	MacAddress MacAddress::lookup_from_ip(const IpAddress& ipAddress) {
	  return MacAddress(); // TODO
	  /*struct ifreq ifr;
	  int sock;


	  int j, k;
	  char *p, addr[32], mask[32], mac[32];


	  //sock = socket(AF_INET, SOCK_STREAM, 0);
	  //sock = socket(AF_INET, SOCK_DGRAM, 0); // yes
	  //sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	  sock = socket(AF_INET, SOCK_PACKET, htons(ETH_P_ARP));

	  if (-1 == sock) {
		  perror("socket() ");
		  return MacAddress();
	  }

	   / *int ret = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));

	  if (-1 == ret) {
		  cout << "ERROR ON SETOPT" << endl;
		  return MacAddress();
	  }*/


	  /*
        if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
                error("socket(SOCK_RAW): %m");
        if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on,
            sizeof(on)) == -1)
                error("setsockopt(IP_HDRINCL): %m");
[...]
and then
sendmsg(sock, somemmem....);*/

	  /*int port = DAC_PORT_COMMS;
	  sockaddr_in server;

	  server.sin_family = AF_INET;
	  server.sin_port = htons(port);
	  server.sin_addr.s_addr = inet_addr("169.254.97.13");

	  int ret = connect(sock, (sockaddr*)&server, sizeof(server)); 

	  if (-1 == ret) {
		cout << "Didn't connect on socket " << sock << " and port " << port << endl;
		return MacAddress();
	  }*/

	  //#ifr.ifr_addr = inet_addr("169.254.97.13");

	  //strncpy(ifr.ifr_name, "eth1", sizeof(ifr.ifr_name)-1);
	  //ifr.ifr_name[sizeof(ifr.ifr_name)-1]='\0';

	  /*if (-1==ioctl(sock, SIOCGIFADDR, &ifr)) {
		  perror("ioctl(SIOCGIFADDR) 2");
		  return MacAddress();
	  } 
	  p = inet_ntoa(((struct sockaddr_in *)(&ifr.ifr_addr))->sin_addr);
	  strncpy(addr, p, sizeof(addr)-1);
	  addr[sizeof(addr)-1]='\0';

	  if (-1==ioctl(sock, SIOCGIFNETMASK, &ifr)) {
		  perror("ioctl(SIOCGIFNETMASK) 3");
			  return MacAddress();
		  }
		  p = inet_ntoa(((struct sockaddr_in *)(&ifr.ifr_netmask))->sin_addr);
		  strncpy(mask,p,sizeof(mask)-1);
		  mask[sizeof(mask)-1]='\0';

		  if (-1==ioctl(sock, SIOCGIFHWADDR, &ifr)) {
		  perror("ioctl(SIOCGIFHWADDR) 4");
		  return MacAddress();
	  }
	  for (j=0, k=0; j<6; j++) {
		  k+=snprintf(mac+k, sizeof(mac)-k-1, j ? ":%02X" : "%02X",
			  (int)(unsigned int)(unsigned char)ifr.ifr_hwaddr.sa_data[j]);
	  }
	  mac[sizeof(mac)-1]='\0';

	  printf("\n");
	  printf("name:    %s\n",ifr.ifr_name);
	  printf("address: %s\n",addr);
	  printf("netmask: %s\n",mask);
	  printf("macaddr: %s\n",mac);
	  printf("\n");

	  close(sock);

	  return MacAddress();

	  / *sock = socket(AF_INET, SOCK_DGRAM, 0);
  
	  strcpy(ifr.ifr_name, "eth0");
	  ifr.ifr_addr.sa_family = AF_INET;
	  
	  if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
		cout << "Error" << endl;
		return MacAddress();
	  }
	  
	  char mac[6];

	  memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);

	  cout << "Mac: " + string(mac) << endl;
		
	  close(sock);

	  return MacAddress();*/
	}

	bool MacAddress::operator==(const MacAddress& other) const {
	  // TODO: Colons, and soon other member vars
	  return (strcasecmp(macString.c_str(), other.macString.c_str()) == 0);
	}

  } // end namespace Network
} // end namespace LE

