#include "Stp.hpp"

/* Note:
 * for servo mode, the set-point (on 0 degree) must be defined first
 * before driving any stepper motor
 */

//asume that our stepper motor here has specification of
//1.8 degree of rotation in each its step, each spec of stepper
//motor may differ
//1.8 degree per step; in servo motor mode
Stp motor(1.8,MODE_SERVO);

void setup(){
  motor.toPins(4,5,6,7);  //pin configuration
  motor.spin_speed(100);	//delay (in milli second) per step
}

void loop(){
  //asume that on the hardware, a set point (of 0 degree)
  //position has been set. So that the stepper can move 
  //around 0 deg to 360 deg consistently
  motor = 5;    //turn 5 degree
  delay(1000);
  motor = 16;   //turn 16 degree
  delay(1000);
  motor = 30;   //turn 30 degree
  delay(1000);
  motor = 12;   //turn 12 degree
  delay(1000);
  motor = 1;    //turn 1 degree
  delay(1000);
}
