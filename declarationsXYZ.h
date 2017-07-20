#ifndef declarationsXYZ_h
#define declarationsXYZ_h

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>
//#include <AccelStepper.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //Default address, no jumpers
//Adafruit_MotorShield AFMSbot(0x61); //Rightmost jumper closed
Adafruit_DCMotor *myMotor = AFMS.getMotor(2);
//Adafruit_StepperMotor *myMotorStepper = AFMStop.getStepper(200, 2); //M3,M4
Adafruit_StepperMotor *myMotorStepper = AFMS.getStepper(200, 2);

//Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
//Adafruit_StepperMotor *myMotorStepper = AFMSbot.getStepper(200, 2);

Servo myServo1;
Servo myServo2;
Servo myServo3;

///////This code is for accel stepper.

//// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
//// wrappers for the first motor!
//void forwardstep1() {  
//  myMotorStepper->onestep(FORWARD, DOUBLE);
//}
//void backwardstep1() {  
//  myMotorStepper->onestep(BACKWARD, DOUBLE);
//}
//// wrappers for the second motor!
//void forwardstep2() {  
//  myMotorStepper2->onestep(FORWARD, DOUBLE);
//}
//void backwardstep2() {  
//  myMotorStepper2->onestep(BACKWARD, DOUBLE);
//}
//// Now we'll wrap the 3 steppers in an AccelStepper object
//AccelStepper stepper1(forwardstep1, backwardstep1);
//AccelStepper stepper2(forwardstep2, backwardstep2);

long position_y = 0;
long position_x = 90;
long position_z = 0;
long position_w = 0;

long position_y_desired = 0;
long position_x_desired = 90;
long position_z_desired = 0;
long position_w_desired = 0;
long position_w_target = 0;
int yspeed = 0;
//int step_w = 0;
int step_z = 0;
int stepsize = 1;
int quartRot = 450;
int nRot = 1;
int i;
int conversionFactor = 240;
int inByte = 0;
int command = 0;
//int whatAngle = 90;

int current_y, speed;

int tailbeatfreq = 2;
int tailbeatfreqcycle = round(1000/tailbeatfreq/10);
int tailbeatfreqcyclecounter = 0;
int tailbeatstate = 0;


#endif
