#include <Streaming.h>
#include "L298Lib.h"

void setup() {
  L298_setup(); // initialize L298 motor control board
  DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD); // set right motor to PWR_STOP
  DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD); // set left motor to PWR_STOP
}

void loop() {
  int raw_data = analogRead(3); // get A3 input value

  // here I use 500 as threshold
  if(raw_data < 500) {
    DriveSingleMotor(MOTOR_M1, 5, DIR_FORWARD); // right motor starts to run in 5 speed
    DriveSingleMotor(MOTOR_M2, PWR_STOP, DIR_FORWARD); 
    digitalWrite(13, HIGH); // LED on
  } else {
    DriveSingleMotor(MOTOR_M1, PWR_STOP, DIR_FORWARD); 
    DriveSingleMotor(MOTOR_M2, 5, DIR_FORWARD); // left motor starts to run in 5 speed
    digitalWrite(13, LOW); // LED off
  }
}
