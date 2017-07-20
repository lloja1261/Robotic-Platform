/*
  UDPinit.h - Library for compressing main gateway code
*/
#ifndef UDPinit_h
#define UDPinit_h

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "UDPdeclaration.h"
#include "UDPlib.h"

void initializeUDP(void){
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}

#endif
