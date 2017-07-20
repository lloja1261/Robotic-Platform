/*
  UDPlib.h - Library for compressing main gateway code
*/
#ifndef UDPlib_h
#define UDPlib_h

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "UDPdeclaration.h"

//int bit1, bit2, bit3, bit4, bit5, bit6, bit7

void printIP(void) {
  IPAddress remote = Udp.remoteIP(); //print IPaddress
  for (int i =0; i < 4; i++) { Serial.print(remote[i], DEC); 
    if (i < 3) { Serial.print("."); }
  }
}

void printPort(void){
  Serial.print(Udp.remotePort());
}

void printPacketBuffer(void){
  Serial.print(packetBuffer);
}

void readPacketBuffer(void){
  Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
}

void clearPacketBuffer(void){
  for(int i=0;i<UDP_TX_PACKET_MAX_SIZE;i++) packetBuffer[i] = 0; //clear buffer
}

#endif
