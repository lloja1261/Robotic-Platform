// This arduino program part runs the platform except z-axis
// Motor shield without jumper soldering is used

#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include <AccelStepper.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>
#include "declarationsXYZ.h"
#include "initXYZ.h"
#include "functionXYZ.h"

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>// UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include "UDPdeclaration.h"
#include "UDPlib.h"
#include "UDPinit.h"

#include <MsTimer2.h>

int translate_x, translate_y, translate_z, translate_w;
unsigned long time1;
unsigned long pretime;
double period = 0;
int numiter=0;
int avg_iter = 0;
void setup(){
  initializeXYZ();
  current_y = position_y;
  speed = 250;
//  Serial.println("XYZ passed");
  initializeUDP();
//  Serial.println("Ethernet passed");
  digitalWrite(10, LOW);//safely set SPI to turn on

  MsTimer2::set(500, givetailbeatstate); // 500ms period
  MsTimer2::start();
}

void loop(){

  if(Serial.available()>0){
    inByte = Serial.read();
    Serial.println((inByte-48));  
    command = (inByte-48);
    if(command == 0){ move_y(position_y, 0, 250);}
    if(command == 1){ move_y(position_y, -200, 250);
                      position_y = 0;
                      }
    if(command == 2){ move_y(position_y, 3000, 250);}  //it is going to be moving in the y direction by some units
    if(command == 3){ move_y(position_y, 4000, 250);}
    if(command == 4){ move_x(180);}
//    if(command == 5){ move_z(600, 0, 1000);}
//    if(command == 6){ move_z(0, 600, 1000);}    

    if(command == 7){ 
      position_x_desired = 50; //90
      yspeed = 0;
      current_y = position_y;
      position_y_desired = 0; //0
      position_z_desired = 0;
      position_w_desired = 200;
    }
    if(command == 8){ 
      position_x_desired = 90; 
      yspeed = 0;
      current_y = position_y;
      position_y_desired = 0;
      position_z_desired = 0;
      position_w_desired = 0;
    }
    if(command == 9){ 
      position_x_desired = 140; 
      yspeed = 0;
      current_y = position_y;
      position_y_desired = 0;
      position_z_desired = 0;
      position_w_desired = 100;
    }  
  }


  //use Ethernet device, if there's data available, read a packet
  int packetSize = Udp.parsePacket(); // the udp packet size is the udp.parsepacket-- the parse packet is defined by the packetSize 
//  Serial.print("Packet size:");
//  Serial.println(packetSize);
  if(packetSize) {  //the packet size is coming from the parsePacket. if zero, the program would not run, but if not, the program will run 
    // recieved UDP packets
    readPacketBuffer(); // read the packet into packetBuffer  ---  reduces loss of packet and delays in streaming
//    Serial.print("Received packet of size "); Serial.print(packetSize); Serial.print(" From "); printIP(); Serial.print(", port "); printPort(); Serial.print(" Contents:"); printPacketBuffer(); Serial.println();
    //translte code to variables, typical message "x:150,y:4500,z:2400"(old)
    //translte code to variables, typical message "x:150y:4500z:2400A:150"(new)
    translate_x = (packetBuffer[2]-48)*100+ (packetBuffer[3]-48)*10+ (packetBuffer[4]-48) ;  // the packet buffer allows one to create a storage for the packet 
    translate_y = (packetBuffer[7]-48)*1000+ (packetBuffer[8]-48)*100+ (packetBuffer[9]-48)*10+ (packetBuffer[10]-48) ;
    translate_z = (packetBuffer[13]-48)*1000+ (packetBuffer[14]-48)*100+ (packetBuffer[15]-48)*10+ (packetBuffer[16]-48);
    translate_w = (packetBuffer[19]-48)*100+ (packetBuffer[20]-48)*10+ (packetBuffer[21]-48) -180 ;
//    Serial.println(translate_z);
//    int len = length(translate_z);
    int sendz = translate_z / 4;  //the latter one is soted in the first variable
    Serial.write(sendz);
    //protection
    if(packetSize > 20){  //if the paqcket size is greater than 20 then run this part of the code. 
      
      if(translate_x<50)   translate_x = 50; //this allows for translating the objects
      if(translate_x>140)  translate_x = 140;
      if(translate_y>4000) translate_y = 4000; //allows for translating the y axis
      if(translate_y<0)    translate_y = 0;          
      if(translate_z>1000) translate_z = 1000; //allows for translating the z axis
      if(translate_z<0)    translate_z = 0;  
//      if(translate_w<10)      translate_w = 10;
//      if(translate_w>170)     translate_w = 170;  
      //insert variable to desired positions
      position_x_desired = translate_x;  //it will translate the object by the desired position
//      Serial.print("Xpos: ");
//    Serial.println(position_x_desired);
//
//      Serial.print("translateX: ");
//    Serial.println(translate_x);
    
      current_y = position_y;       // the current y is now defined as the position of the y
      position_y_desired = translate_y;    // it will translate the object with the desired position
      position_z_desired = translate_z;   //it will translate the object with the desired position
//      position_w_desired = translate_w;
    }
    //exit
    clearPacketBuffer(); // clear packetBuffer
    // send a UDP reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); Udp.write(ReplyBuffer); Udp.endPacket();   //it will connect with the motors
  }


//  tailbeatfreqcyclecounter = tailbeatfreqcyclecounter+1;
//  if(tailbeatfreqcyclecounter%tailbeatfreqcycle == 0){
//    tailbeatstate=(tailbeatstate+1)%2;
//  }

/**
 * This is the way position x, y, and z are defined:
 * x = 30 to 150, starting at 90
 * y = 0 to 4500, starting at 0
 * z = 0 to 2400,starting at 0
 * w = 10 to 170,starting at 90
 **/
//  Serial.println(tailbeatstate);
//  Serial.println("Hi");
  
  updateALL();
  updateZW();


  
//Serial.print("x:");
//Serial.print(position_x);
//Serial.print(" y:");
//Serial.print(position_y);
//Serial.print(" yspeed:");
//Serial.print(yspeed);
////Serial.print(" z:");
////Serial.print(position_z);
//Serial.print(" w:");
//Serial.println(position_w);
//  Serial.println("Updated");
  delay(10); // in milliseconds

// 
//
//  pretime = time1;
//  time1 = millis();
//  period = (time1-pretime);
//  Serial.print(" Period time: ");
//  Serial.print(period);
//  Serial.print(" Average time: ");
//  Serial.println(avg_iter);
//
//  avg_iter = time1/numiter;
//  
//  numiter = numiter + 1;
  
}

