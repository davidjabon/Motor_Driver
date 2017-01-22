#include <Wire.h>
#include <Motor_Driver.h>


void setup() {
  //Declare the driver and initialize it:
  Motor_Driver MD = Motor_Driver();
  MD.begin();
  //Set directions for motors
  MD.setPin(MOTOR2_PIN1,HIGH);
  MD.setPin(MOTOR2_PIN2,LOW);
  
  MD.setPin(MOTOR4_PIN1,LOW);
  MD.setPin(MOTOR4_PIN2,HIGH);

  //Turn motors on at a certain speed between 0 and 4095.
  MD.set_motor_speed(2,2047);
  MD.set_motor_speed(4,2047);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
