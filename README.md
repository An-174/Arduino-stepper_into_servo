# Arduino-stepper_into_servo

This arduino library is intended to use a stepper motor as servo by assigning a 'degree' value directly to it
just install this libray to your arduino and see the example about how to use.

asume that our stepper motor here has specification of
1.8 degree of rotation in each its step, each spec of stepper
motor may differ
1.8 degree per step; in servo motor mode

Stp motor(1.8,MODE_SERVO);


Setup:
  motor.toPins(4,5,6,7);      -> pin configuration
  motor.spin_speed(100);      -> delay (in milli second) per step
  
 note that there is a set point that have to be set on the stepper motor, meaning that the condition has to be in 0, 30, 25 or any other degree.

or see for detail:
https://sci-gf.blogspot.com/2019/08/driving-stepper-as-servo-motor-using.html
