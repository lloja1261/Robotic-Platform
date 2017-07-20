
#ifndef initXYZ_h
#define initXYZ_h

#include <Wire.h>   // wire.h is something that comes with the program
#include <Adafruit_MotorShield.h>  //this is an .h file. 
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>
#include "declarationsXYZ.h"
#include <AccelStepper.h>

void read_quadrature(){  
  static int8_t lookup_table[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};
  static uint8_t enc_val = 0;
  enc_val = enc_val << 2;
  enc_val = enc_val | ((PIND & 0b1100)  >>2);
  position_y = position_y + lookup_table[enc_val & 0b1111];
}

void initializeXYZ(void){
  Serial.begin(38400);     
  Serial.println("Started");
  attachInterrupt(0, read_quadrature, CHANGE);
  attachInterrupt(1, read_quadrature, CHANGE);
  AFMS.begin();  // create with the default frequency 1.6KHz
//  AFMSbot.begin();  // create with the default frequency 1.6KHz
  myServo1.attach(8);
  myServo2.attach(9);
//  myServo3.attach(7);
  myServo1.write(90);
  myServo2.write(90);
//  myServo3.write(90);
  
  myMotor->setSpeed(250);
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);

//  myMotorStepper->setSpeed(200); 
  myMotorStepper->setSpeed(200);

//  stepper1.setMaxSpeed(200.0);
//  stepper1.setAcceleration(100.0);
//  stepper1.moveTo(0);
//  stepper2.setMaxSpeed(200.0);
//  stepper2.setAcceleration(100.0);
//  stepper2.moveTo(0);
  delay(1000);
}




#endif          
