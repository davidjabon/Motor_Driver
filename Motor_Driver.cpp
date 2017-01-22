#include "Arduino.h"
#include "Motor_Driver.h"
#include "inttypes.h"
#include "Wire.h"

/*
   Motor_Driver - Simplified Library for using Adafruit 2.3 Motor Shield for DC Motors only
   Created by David Jabon
   The purpose of this simplified library is for instruction of students.  It is very simple and requires the
   the user to set the pin directions to set the directions of the motors.  This library was kept simple
   purposely so that students are required to set the direction and set the speed.
   Released into the public domain.
*/



Motor_Driver::Motor_Driver(uint8_t address)
{
	i2c_address = address;
}

void Motor_Driver::begin(uint8_t prescale)
{
	Wire.begin();
    setPRESCALE(prescale);
}

void Motor_Driver::setPRESCALE(uint8_t prescale)
{
	// We set the pre_scale  by default to give the maximum frequency  which is PRE_SCALE=0x03.  
	//The lowest freqency is PRE_SCALE = 0xFF.  See page 25 of the PCA9685 datasheet.  
	// The formula for the frequency is supposedly 25MHz/(4096*(PRE_SCALE+1)).
	// However I have found that the measured max frequency is  1708 Hz.  The minimum is 27 Hz.
	// Default on power up is 0x1E  = 63 about 200 Hz.
	
	//The PRE_SCALE register can only be set when the SLEEP bit of MODE1 is set to 1 (i.e. sleep mode).
	
	//Read the current MODE1 register.
	uint8_t current_MODE1 = read_reg(PCA9685_MODE1); //Note: the default  power up MODE1 register value is 0x11.
	//Set up the commands we will be needing 
    current_MODE1 = current_MODE1 & 0x7F; //Set restart bit to 0
	uint8_t sleep = current_MODE1 | 0x10;  // Set sleep bit to 1
	uint8_t wake = current_MODE1 & 0xEF;  // Set sleep bit to 0
	uint8_t restart = wake | 0xA0;  // set Auto-increment bit 5 = 1 and restart bit 7 = 1
	// Go to sleep
	write_reg(PCA9685_MODE1, sleep); 
	// Set the PRE_SCALE
    write_reg(PCA9685_PRESCALE, prescale); 
	// Wake
	write_reg(PCA9685_MODE1, wake);
	// Need to wait at least 500 microseconds before logic 1 is written to the RESTART bit.
    delay(1);
	// Restart
   write_reg(PCA9685_MODE1, restart);  

	
	
	
}


void Motor_Driver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  Wire.beginTransmission(i2c_address);
  Wire.write(LED0_ON_L+4*num);
  Wire.write(on);
  Wire.write(on>>8);
  Wire.write(off);
  Wire.write(off>>8);
  Wire.endTransmission();
}

 void Motor_Driver::set_motor_speed(uint8_t motor_number, uint16_t speed){
	//These pin numbers correspond to the PWM inputs of the TB6612 Drivers
	switch (motor_number) {
    case 1:
      setPWM(8,0,speed);
      break;
    case 2:
      setPWM(13,0,speed);
      break;
	case 3:
      setPWM(2,0,speed);
      break;
	case 4:
      setPWM(7,0,speed);
      break;
    default: 
      // if nothing matches, do nothing
    break;
  }

 }
 


void Motor_Driver::setPin(uint8_t pin, boolean value) {
    if (value == LOW)
    setPWM(pin, 0, 0);
  else
    setPWM(pin, 0, 4095);
}



uint8_t Motor_Driver::read_reg(uint8_t reg)
{
	Wire.beginTransmission(i2c_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(i2c_address, 1);
    return Wire.read();

}


void Motor_Driver::write_reg(uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(i2c_address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}


















