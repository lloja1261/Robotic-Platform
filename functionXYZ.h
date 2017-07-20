#ifndef functionXYZ_h
#define functionXYZ_h

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>
#include "declarationsXYZ.h"
//#include <AccelStepper.h>


void updateALL(void) {
  //---THIS IS FOR X AXIS CODE
  if(position_x_desired - position_x > 10){   //desired position minus the object position
    for(; position_x_desired > position_x; position_x+=1){   //when the desired position is greater than the object position then keep adding 1 until equal?
      myServo1.write(position_x);   
      myServo2.write(180-position_x);
      delay(15);
    }
  }
  if(position_x_desired - position_x < -10){
    for(; position_x > position_x_desired; position_x-=1){
      myServo1.write(position_x);
      myServo2.write(180-position_x);
      delay(15); //15 milliseconds
    }
  }

 //---THIS IS FOR Y AXIS CODE
  if(position_y_desired > current_y){
    if( position_y > position_y_desired){
      myMotor->setSpeed(0);
      myMotor->run(RELEASE); 
    }
    if( position_y < position_y_desired){
      myMotor->setSpeed(50);
      if(position_y_desired >= 4600) {Serial.println("Not a valid position"); myMotor->run(RELEASE); }
      else{
//          Serial.println(position_y);
        myMotor->run(FORWARD);
        if( position_y <= (((position_y_desired-current_y)/5)+current_y)){
//            Serial.println(position_y);
          myMotor->setSpeed(speed);
        }
        if( position_y <= ((((position_y_desired-current_y)*4)/5)+current_y)){
//            Serial.println(position_y);
          myMotor->setSpeed(speed);
        }
        if( position_y <= position_y_desired){
//            Serial.println(position_y);
          myMotor->setSpeed(abs(position_y_desired-position_y)*185/abs(position_y_desired-current_y)+70);
        }
      }
    }
  }

  if(position_y_desired < current_y){
    if( position_y < position_y_desired){
      myMotor->setSpeed(0);
      myMotor->run(RELEASE); 
    }
    if(position_y > position_y_desired){
      myMotor->setSpeed(50);
        if(position_y_desired <= -100) {Serial.println("Not a valid position"); myMotor->run(RELEASE); }
        else {
//          Serial.println(position_y);
        myMotor->run(BACKWARD);
        if( position_y >= (current_y-((current_y-position_y_desired)/5))){
//            Serial.println(position_y);
          myMotor->setSpeed(speed);
        }
        if( position_y >= (current_y-(((current_y-position_y_desired)*4)/5))){
//            Serial.println(position_y);
          myMotor->setSpeed(speed);
        }
        if( position_y >= position_y_desired){
          myMotor->setSpeed(abs(position_y-position_y_desired)*185/abs(current_y-position_y_desired)+70);
        }
      }
    }
  }

  
//  // Y axis control based on speed
//
//   if(position_y_desired > position_y)
//   {
//     yspeed += 10;
//     if(abs(yspeed) > 250){
//       yspeed = 250;
////       Serial.println("Speed up");
//     }
//     
//     if(yspeed >= 0){
//       myMotor->run(FORWARD);
//       myMotor->setSpeed(abs(yspeed));
//     }
//     else{
//       myMotor->run(BACKWARD);
//       myMotor->setSpeed(abs(yspeed));
//     }
//   }
//   else if (position_y_desired < position_y){
//     yspeed -= 10;
//     if(yspeed < -250){
//       yspeed = -250;
////       Serial.println("Speed down");
//     }
//
//     if(yspeed >= 0){
//       myMotor->run(FORWARD);
//       myMotor->setSpeed(abs(yspeed));
//     }
//     else{
//       myMotor->run(BACKWARD);
//       myMotor->setSpeed(abs(yspeed));
//     }
//   }
//   else{
//     myMotor->setSpeed(0);
//     myMotor->run(RELEASE);
//   }
//
//  if(position_y > 4200){
//    yspeed = -100;
//    myMotor->run(BACKWARD);
//    myMotor->setSpeed(abs(yspeed));
//    delay(100);
////    myMotor->run(RELEASE);
//  }
//  if(position_y < -100){
//    yspeed = 100;
//    myMotor->run(FORWARD);
//    myMotor->setSpeed(abs(yspeed));
//    delay(100);
////    myMotor->run(RELEASE);
//  }
  
//  Serial.println(position_y);
  
  // Y axis control based on position 

  
  
}
void updateZW(void) {
  //---THIS IS FOR Z AXIS CODE

//  step_z = abs(position_z_desired - position_z);

//    if(position_z_desired - position_z > 100){
////    Serial.println("z move up");
//    myMotorStepper->setSpeed(200); 
//    myMotorStepper->step(stepsize, FORWARD, DOUBLE);
//    position_z+=stepsize;
//  }
//  if(position_z_desired - position_z < -100){
////    Serial.println("z move down");
//    myMotorStepper->setSpeed(200); 
//    myMotorStepper->step(stepsize, BACKWARD, DOUBLE);
//    position_z-=stepsize;
//  }


//  stepper1.moveTo(step_z);
//  if (stepper1.distanceToGo() == 0){
    
//    stepper1.moveTo(-stepper1.currentPosition());
  
  

  
//  stepper1.moveTo(-stepper1.currentPosition());


  //---This is a new W axis code using a stepper motor

//if(yspeed > 150){
//  position_w_desired = 50;
//}
//else if(yspeed < -150){
//  position_w_desired = -50;
//}
//else{
//  position_w_desired = 0;
//}

position_w_desired = yspeed / (-6);
//Serial.println("position_w_desired");
int step_w = abs(position_w_desired-position_w);
if(position_w_desired > position_w){
//    Serial.println("w move up");
    myMotorStepper->setSpeed(250); 
    myMotorStepper->step(1, FORWARD, DOUBLE);
    position_w+=1;
  }
if(position_w_desired < position_w){
//    Serial.println("w move down");
    myMotorStepper->setSpeed(250); 
    myMotorStepper->step(1, BACKWARD, DOUBLE);
    position_w-=1;
  }
}
//


  // if(tailbeatstate){
  //   position_w_target = position_w_desired + 30;
  

//    step_w = position_w_target / 1.8;
  
//  if(position_w_target > position_w){
//    myMotorStepper2->setSpeed(200);
//    myMotorStepper2->step(step_w, FORWARD, DOUBLE);
//    position_w+=step_w;
//  }
//  if(position_w_target < position_w){
////    Serial.println("move down");
//    myMotorStepper2->setSpeed(200); 
//    myMotorStepper2->step(step_w, BACKWARD, DOUBLE);
//    position_w-=step_w;
//  }
//
//  stepper2.moveTo(step_w);
//  
//  if (stepper2.distanceToGo() == 0){
//     
//     stepper2.moveTo(-stepper2.currentPosition());

// Serial.print("Step_w = ");
// Serial.println(step_w);
//  stepper1.run();
//  stepper2.run();
//  position_w=step_w;
//  position_z=step_z;


  // }
//   else{
//     position_w_target = position_w_desired;
//   if(position_w_target > position_w){
//     myMotorStepper2->setSpeed(200);
//     myMotorStepper2->step(step_w, FORWARD, DOUBLE);
//     position_w+=step_w;
//   }
//   if(position_w_target < position_w){
// //    Serial.println("move down");
//     myMotorStepper2->setSpeed(200); 
//     myMotorStepper2->step(step_w, BACKWARD, DOUBLE);
//     position_w-=step_w;
//   }  
//   }

//  
//    //---THIS IS FOR W AXIS CODE using Servo motor
//    if(position_w_desired > position_w){
//      for(; position_w_desired > position_w; position_w+=1){
//  //      if(tailbeatstate)
//  //        myServo3.write(position_w);
//  //      else
//  //        myServo3.write(position_w+20);
//      }
//    }
//    if(position_w > position_w_desired){
//      for(; position_w > position_w_desired; position_w-=1){
//  //      if(tailbeatstate)
//  //        myServo3.write(position_w);
//  //      else
//  //        myServo3.write(position_w+20);
//      }
//    }
//  //  if(position_w == position_w_desired){
//  //    if(tailbeatstate)
//  //      myServo3.write(position_w);
//  //    else
//  //      myServo3.write(position_w+20);
//  //  }



void givetailbeatstate(void) {
  tailbeatstate=(tailbeatstate+1)%2;
//  if(tailbeatstate)
//  position_w_target = position_w_desired + 5; //use -5 in tail beat motion 
//    myServo3.write(position_w);
//  else
//  position_w_target = position_w_desired - 5; //use +5 in tail beat motion
//    myServo3.write(position_w+10);
}





void move_x(int final_x) {
  if(final_x > position_x){
    for(; final_x > position_x; position_x+=1){
      myServo1.write(position_x);
      myServo2.write(180-position_x);
      delay(10);
    }
  }
  if(position_x > final_x){
    for(; position_x > final_x; position_x-=1){
      myServo1.write(position_x);
      myServo2.write(180-position_x);
      delay(10);
    }
  }
}

void move_y(int current_y, int final_y, int speed){
  myMotor->setSpeed(250);
  if(final_y > current_y){
    if(final_y >= 5000) {Serial.println("Not a valid position"); myMotor->run(RELEASE); }
    else{
      Serial.println("move_y: up");
      myMotor->run(FORWARD);
      while( position_y <= (((final_y-current_y)/5)+current_y)){
        myMotor->setSpeed(speed);
        delay(10);
      }
      while( position_y <= ((((final_y-current_y)*4)/5)+current_y)){
        myMotor->setSpeed(speed);
        delay(10);
      }
      while( position_y <= final_y){
        myMotor->setSpeed(abs(final_y-position_y)*185/abs(final_y-current_y)+70);
        delay(10);
      }
    }
  }
  if(current_y > final_y){
    myMotor->setSpeed(250);
      if(final_y <= -1000) {Serial.println("Not a valid position"); myMotor->run(RELEASE); }
      else {
      Serial.println("move_y: down");
      myMotor->run(BACKWARD);
      while( position_y >= (current_y-((current_y-final_y)/5))){
        myMotor->setSpeed(speed);
        delay(10);
      }
      while( position_y >= (current_y-(((current_y-final_y)*4)/5))){
        myMotor->setSpeed(speed);
        delay(10);
      }
      while( position_y >= final_y){
        myMotor->setSpeed(abs(position_y-final_y)*185/abs(current_y-final_y)+70);
        delay(10);
      }
    }
  }
  myMotor->setSpeed(0);
}
//
//void move_z (int current_z, int final_z, int zspeed){
//  Serial.print("called z");
//  if(current_z >= final_z) {
//    Serial.print("move up");
//    myMotorStepper->setSpeed(zspeed); 
//    myMotorStepper->step(current_z-final_z, BACKWARD, DOUBLE);
//  }
//  if(final_z >= current_z) {
//    Serial.print("move down");
//    myMotorStepper->setSpeed(zspeed); 
//    myMotorStepper->step(final_z-current_z, FORWARD, DOUBLE);
//  }
//}

#endif
