/*
First idea for the Mecanum Car with BT module

*/

#include "MecanumRCCar.h"

// creating a mecanumRCCar instance, named MRCar
mecanumRCCar MRCar;  //default settings for my project I2C details sda_pin=8, scl_pin=9, ICaddress=0x6c

motor FrontLeftMotor(MOTOR_1);  //create 4 motor object, regaddress in the header file, all with zero spd
motor FrontRightMotor(MOTOR_2);
motor BackLeftMotor(MOTOR_3);
motor BackRightMotor(MOTOR_4);

direction FL(1, 0, 1, 1, 0);
direction FW(2, 1, 1, 1, 1);
direction FR(3, 1, 0, 0, 1);
direction L(4, -1, 1, 1, -1);
direction R(6, 1, -1, -1, 1);
direction BL(7, -1, 0, 0, -1);
direction BW(8, -1, -1, -1, -1);
direction BR(9, 0, -1, -1, 0);
direction TL(10, -1, 1, -1, 1);
direction TR(11, 1, -1, 1, -1);
direction STOP(5, 0, 0, 0, 0);

byte BT_received_byte;
byte global_speed = 70;
byte control_command = 2;

void setup() {
  // creating a mecanumRCCar instance, named MRCar


  MRCar.begin();
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (Serial1.available() > 0) {
    control_command = Serial1.read();
    Serial.println(control_command);  //debugging
  }



  switch (control_command) {
    case 1:
      FrontLeftMotor.speed(FL._speed_factor[0] * global_speed);
      FrontRightMotor.speed(FL._speed_factor[1] * global_speed);
      BackLeftMotor.speed(FL._speed_factor[2] * global_speed);
      BackRightMotor.speed(FL._speed_factor[3] * global_speed);

      break;
    case 2:
      FrontLeftMotor.speed(FW._speed_factor[0] * global_speed);
      FrontRightMotor.speed(FW._speed_factor[1] * global_speed);
      BackLeftMotor.speed(FW._speed_factor[2] * global_speed);
      BackRightMotor.speed(FW._speed_factor[3] * global_speed);
      break;
    case 3:
      FrontLeftMotor.speed(FR._speed_factor[0] * global_speed);
      FrontRightMotor.speed(FR._speed_factor[1] * global_speed);
      BackLeftMotor.speed(FR._speed_factor[2] * global_speed);
      BackRightMotor.speed(FR._speed_factor[3] * global_speed);
      break;
    case 4:
      FrontLeftMotor.speed(L._speed_factor[0] * global_speed);
      FrontRightMotor.speed(L._speed_factor[1] * global_speed);
      BackLeftMotor.speed(L._speed_factor[2] * global_speed);
      BackRightMotor.speed(L._speed_factor[3] * global_speed);
      break;
    case 6:
      FrontLeftMotor.speed(R._speed_factor[0] * global_speed);
      FrontRightMotor.speed(R._speed_factor[1] * global_speed);
      BackLeftMotor.speed(R._speed_factor[2] * global_speed);
      BackRightMotor.speed(R._speed_factor[3] * global_speed);
      break;
    case 7:
      FrontLeftMotor.speed(BL._speed_factor[0] * global_speed);
      FrontRightMotor.speed(BL._speed_factor[1] * global_speed);
      BackLeftMotor.speed(BL._speed_factor[2] * global_speed);
      BackRightMotor.speed(BL._speed_factor[3] * global_speed);
      break;
    case 8:
      FrontLeftMotor.speed(BW._speed_factor[0] * global_speed);
      FrontRightMotor.speed(BW._speed_factor[1] * global_speed);
      BackLeftMotor.speed(BW._speed_factor[2] * global_speed);
      BackRightMotor.speed(BW._speed_factor[3] * global_speed);
      break;
    case 9:
      FrontLeftMotor.speed(BR._speed_factor[0] * global_speed);
      FrontRightMotor.speed(BR._speed_factor[1] * global_speed);
      BackLeftMotor.speed(BR._speed_factor[2] * global_speed);
      BackRightMotor.speed(BR._speed_factor[3] * global_speed);
      break;
    case 10:
      FrontLeftMotor.speed(TL._speed_factor[0] * global_speed);
      FrontRightMotor.speed(TL._speed_factor[1] * global_speed);
      BackLeftMotor.speed(TL._speed_factor[2] * global_speed);
      BackRightMotor.speed(TL._speed_factor[3] * global_speed);
      break;
    case 11:
      FrontLeftMotor.speed(TR._speed_factor[0] * global_speed);
      FrontRightMotor.speed(TR._speed_factor[1] * global_speed);
      BackLeftMotor.speed(TR._speed_factor[2] * global_speed);
      BackRightMotor.speed(TR._speed_factor[3] * global_speed);
      break;
    case 5:
      FrontLeftMotor.speed(STOP._speed_factor[0] * global_speed);
      FrontRightMotor.speed(STOP._speed_factor[1] * global_speed);
      BackLeftMotor.speed(STOP._speed_factor[2] * global_speed);
      BackRightMotor.speed(STOP._speed_factor[3] * global_speed);
      break;
    default:
      FrontLeftMotor.speed(0);
      FrontRightMotor.speed(0);
      BackLeftMotor.speed(0);
      BackRightMotor.speed(0);
      break;
  }
}