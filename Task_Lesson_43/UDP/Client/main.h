
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512	//Max length of buffer
#define DESTINATION_PORT 8888	//The port on which to send data
#define SOURCE_PORT 56657	//The port on which to send data


#define HEADER_IP_ETHERNET_TYPE 0x0800	// IPv4 Ethernet Type
#define HEADER_IP_VERSIA_IP 0x40	// VERSIA IPv4
#define HEADER_IP_LENGHT_IP_HEADER 0x05	// LENGHT_IP_HEADER 
#define HEADER_IP_TYPE_SERVICE 0x00	// Type of Service

#define HEADER_IP_IDENTIFICATION 0x0000	    // Identification
#define HEADER_IP_FLAGS_FR_OFFSET 0x0000    // Flags and Fragment Offset
#define HEADER_IP_TIME_TO_LIVE 0xFF	    // Time to Live
#define HEADER_IP_TYPE_PROTOCOL 17	    // Type Protocol Up Level (UDP = 0x11)







