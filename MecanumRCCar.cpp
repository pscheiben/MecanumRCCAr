#include "Arduino.h"
#include "MecanumRCCar.h"
#include <Wire.h>


mecanumRCCar::mecanumRCCar(byte sda_pin, byte scl_pin, byte IC_address, int PWM_Frequency) {
  _sda_pin = sda_pin;  //class variables from the function argument
  _scl_pin = scl_pin;
  _IC_address = IC_address;
  _PWM_Frequency = PWM_Frequency;
}

void mecanumRCCar::begin() {
  Wire.setSDA(_sda_pin);        //set I2C data pin number
  Wire.setSCL(_scl_pin);        //set I2C clk pin number
  Wire.setClock(I2C_BUS_FREQ);  //default I2C bus frequency
  Wire.begin();                 //Join to the I2Cbus as Master/Controller (no address)
  reset();                      //after reset everything goes to default
  PWMFreqSet();                 //set PWMFreqency 24Hz to 1536Hz from PCA9685 datasheet
  writeI2CReg(0xfa, 0);         //ALL_LED_ON_L register clear, default = 0x00
  writeI2CReg(0xfb, 0);         //ALL_LED_ON_H register clear, default = 0x10
  writeI2CReg(0xfc, 0);         //ALL_LED_OFF_L register clear, default = 0x00
  writeI2CReg(0xfd, 0);         //ALL_LED_OFF_H register clear, default = 0x10
  SleepModeOff();               //turn on normal mode
}

void mecanumRCCar::reset() {
  Wire.beginTransmission(0);  //I2C protocol address all devices at address zero
  Wire.write(6);              //only data can be acknowledge the 0x06h, which is a SWRST from the PCA9685 datasheet and I2C manual
  Wire.endTransmission();
}

void mecanumRCCar::writeI2CReg(byte reg_addr, byte data)  //write into the specific register
{
  _reg_addr = reg_addr;
  _data = data;
  Wire.beginTransmission(_IC_address);
  Wire.write(_reg_addr);
  Wire.write(_data);
  Wire.endTransmission();  //end transmission
}

byte mecanumRCCar::readI2CReg(byte reg_addr)  //returns the specific register value
{
  _reg_addr = reg_addr;
  Wire.beginTransmission(_IC_address);
  Wire.write(_reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(_IC_address, 1);  //false option will not realease the bus after request, 1 byte
  return (Wire.read());              //returns the readed value
}

void mecanumRCCar::SleepModeOff()  //turn off the default sleep mode
{
  writeI2CReg(0x00, 1);
}

byte mecanumRCCar::CalcPreScValue() {
  return (int(OSCILLATOR_CLK / (4096 * _PWM_Frequency) - 1));  //calculate the prescale value from constructor PWM frequency
}
void mecanumRCCar::PWMFreqSet() {
  writeI2CReg(0x00, 17);                //write b00010001 into Mode1, goes to sleep, must do before changing Prescaler
  writeI2CReg(0xfe, CalcPreScValue());  //according to the PWM_Freq_Value, writes the calculated value into the prescale register
  SleepModeOff();
}
//-----------------------------------------------------------------------//
motor::motor(byte motor_reg_address) {
  _motor_reg_address = motor_reg_address;
}

void motor::writeI2CReg(byte reg_addr, byte data)  //write into the specific register
{
  _reg_addr = reg_addr;
  _data = data;
  Wire.beginTransmission(IC_ADDRESS);
  Wire.write(_reg_addr);
  Wire.write(_data);
  Wire.endTransmission();  //end transmission
}
void motor::speed(int motor_spd) {
  _motor_spd = motor_spd;
  if (_motor_spd >= 0) {
    int _spd_value = (100 - (_motor_spd)) * 4095 / 100;
    //                      Serial.println(_spd_value);                                         //debug
    writeI2CReg(_motor_reg_address, 0xFF);                      //LEDx_OFF_L register the motor xin1 input "turn on"
    writeI2CReg(_motor_reg_address + 1, 0x0F);                  //LEDx_OFF_H register
    writeI2CReg(_motor_reg_address + 4, lowByte(_spd_value));   //LEDx_OFF_L register the motor xin2 input PWM
    writeI2CReg(_motor_reg_address + 5, highByte(_spd_value));  //LEDx_OFF_H register
  } else {
    int _spd_value = (100 - (~_motor_spd)) * 4095 / 100;
    //                  Serial.println(_spd_value);                                             //debug
    writeI2CReg(_motor_reg_address, lowByte(_spd_value));       //LEDx_OFF_L register the motor xin1 input PWM
    writeI2CReg(_motor_reg_address + 1, highByte(_spd_value));  //LEDx_OFF_H register
    writeI2CReg(_motor_reg_address + 4, 0xFF);                  //LEDx_OFF_L register the motor xin2 input "turn on"
    writeI2CReg(_motor_reg_address + 5, 0x0F);                  //LEDx_OFF_H register
  }
}

//-------------------------------------------------------------------------------------------------

direction::direction(byte direction_id, int FL_speed_factor, int FR_speed_factor, int BL_speed_factor, int BR_speed_factor) {
  _direction_id = direction_id;
  _speed_factor[0] = FL_speed_factor;
  _speed_factor[1] = FR_speed_factor;
  _speed_factor[2] = BL_speed_factor;
  _speed_factor[3] = BR_speed_factor;
}