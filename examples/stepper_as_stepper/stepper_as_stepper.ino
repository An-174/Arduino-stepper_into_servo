#include <Stp.hpp>

/* Note:
	Constructor by default is in Stepper mode
	so the instatiation can be done in two ways i.e.,
	1) Stp objName; or
	2) Stp objName(x,Stepper_mode)	with x=0
 */

//Stp motor(0,MODE_STEPPER);  //or:
Stp motor;

void setup() {
  motor.toPins(4,5,6,7);
}

void loop() {
  motor.spin_direction(CCW); //the rotation direction is counterclockwise
  motor = 22;           //step the motor for 22 steps
  delay(1000);
  motor.spin_direction(CW);  //the direction rotation is clockwise
  motor = 14;           //step the motor for 14 steps
  delay(1000);
}
