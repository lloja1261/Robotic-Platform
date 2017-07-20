/*
  UDPdeclaration.h - Library for compressing main gateway code
*/
#ifndef UDPdeclaration_h
#define UDPdeclaration_h

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

unsigned long time;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
//byte mac[] = { 0x60, 0xF8, 0x1D, 0xAC, 0x72, 0x40 }; // Netgear 43
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x7F, 0x20 }; //Previous
//IPAddress ip(192, 168, 1, 2); // Netgear 43
IPAddress ip(192, 168, 1, 177); //Previous

unsigned int localPort = 8888;      // local port to listen on
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

#endif
