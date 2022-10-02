#ifndef MecanumRCCar_h  //to avoid multiple include during comply
#define MecanumRCCar_h
#include "Arduino.h"  //call the arduino basic library, must be in double "

#define SDA_PIN 8
#define SCL_PIN 9
#define IC_ADDRESS 0x6c
#define I2C_BUS_FREQ 100000
#define OSCILLATOR_CLK 25000000  //25-27 Mhz, need to measure for exact value if necessarry
#define PWM_FREQ 200
#define MOTOR_1 0x28  //Motor LED8_OFF_L register address one motor using 8 register to control
#define MOTOR_2 0x30
#define MOTOR_3 0x38
#define MOTOR_4 0x40

class mecanumRCCar {  //create a class named mecanumRCCar
public:

  mecanumRCCar(byte sda_pin = SDA_PIN, byte scl_pin = SCL_PIN, byte IC_address = IC_ADDRESS, int PWM_Frequency = PWM_FREQ);
  byte _sda_pin;  //class variables according to the constructor argument
  byte _scl_pin;
  byte _IC_address;
  byte _reg_addr;
  byte _data;
  int _PWM_Frequency;
  void begin();
  void reset();
  void writeI2CReg(byte reg_addr, byte data);  //write into the specific register
  byte readI2CReg(byte reg_addr);              //returns the specific register value
  void SleepModeOff();                         //change one bit, to awake the board
  byte CalcPreScValue();
  void PWMFreqSet();


private:


};  //; is mandatory syntax


class motor {  //create a class named motor
public:
  motor(byte motor_reg_address);
  byte _motor_reg_address;  //class variables declaration

  void writeI2CReg(byte reg_addr, byte data);
  byte _reg_addr;
  byte _data;
  void speed(int motor_spd);
  int _motor_spd;


private:
};


class direction {
public:
  direction(byte direction_id, int FL_speed_factor, int FR_speed_factor, int BL_speed_factor, int BR_speed_factor);
  int _speed_factor[4];
  byte _direction_id;
  byte _global_speed;
  void movecar(byte global_speed);
  void create();
private:
};


#endif  //to avoid multiple include during comply