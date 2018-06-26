#include <Streaming.h>
#include "L298Lib.h"

void setup() {
  L298_setup(); // initialize L298 motor control board
  DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD); // set right motor to PWR_STOP
  DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD); // set left motor to PWR_STOP
}

void loop() {
  int raw_data_left = analogRead(1); // get A1 (left) input value
  int raw_data_middle = analogRead(3); // get A3 (middle) input value
  int raw_data_right = analogRead(5); // get A5 (right) input value
  
  // here I use 500 as threshold
  // black: > 500
  // white: < 500
  bool left = raw_data_left > 500 ? true : false;
  bool middle = raw_data_middle > 500 ? true : false;
  bool right = raw_data_right > 500 ? true : false;

  // if middle detects black
  if(middle) {
    if(left && right) { // cliff
      // stop
      DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD); 
      DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD); 
      // pause for 0.5 sec
      delay(500);

      // then go backward
      DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_BACKWARD); 
      DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_BACKWARD); 
    } else if(left) { // turn left
      DriveSingleMotor(MOTOR_M1, 2, DIR_FORWARD); 
      DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD); 
    } else if(right) { // turn right
      DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD); 
      DriveSingleMotor(MOTOR_M2, 2, DIR_FORWARD); 
    } else { // go straight
      DriveSingleMotor(MOTOR_M1, 2, DIR_FORWARD); 
      DriveSingleMotor(MOTOR_M2, 2, DIR_FORWARD); 
    }
  }

  // if all detects white, which means the car is out of track
  if(middle && left && right) { // go backward
    DriveSingleMotor(MOTOR_M1, 2, DIR_BACKWARD); 
    DriveSingleMotor(MOTOR_M2, 2, DIR_BACKWARD); 
  }

  delay(1000);
}
