/*
   Motor_Driver.h - Simplified Library for using Adafruit 2.3 Motor Shield for Motors only
   Created by David Jabon
   Released into the public domain
*/

#ifndef Motor_Driver_h
#define Motor_Driver_h

#include "Arduino.h"
#include <inttypes.h>
#include <Wire.h>

/* 
PCA9685 Definitions
*/

#define PCA9685_SUBADR1 0x02
#define PCA9685_SUBADR2 0x03
#define PCA9685_SUBADR3 0x04

#define PCA9685_MODE1 0x00
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD 
 
// Pin Definitions.  While it doesn't matter much in practice, the motor pins
// go from left to right on the headers when facing the inserts:
// M1_1, M1_2, GND, M2_1, M2_2   and
// M3_1, M3_2, GND, M4_1, M4_2

#define MOTOR1_PIN1 10
#define MOTOR1_PIN2 9
#define MOTOR2_PIN1 12
#define MOTOR2_PIN2 11
#define MOTOR3_PIN1 4
#define MOTOR3_PIN2 3
#define MOTOR4_PIN1 6
#define MOTOR4_PIN2 5

class Motor_Driver
{
public:
	Motor_Driver(uint8_t address = 0x60);
	void begin(uint8_t prescale = 0x03);
	void setPin(uint8_t pin, boolean value);
	void set_motor_speed(uint8_t, uint16_t speed);
private:
	uint8_t i2c_address;
	void setPRESCALE(uint8_t prescale);
	uint8_t read_reg(uint8_t reg);
	void write_reg(uint8_t reg, uint8_t value);
	void setPWM(uint8_t num, uint16_t on, uint16_t off);
};

#endif
