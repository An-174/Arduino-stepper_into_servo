 /* Stp.hpp - library for Steper into Servo
  
  Copyright (c) An Priyatna 2019

  The library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef STP_
#define STP_

#define CW					1
#define CCW					0
#define MODE_SERVO		1
#define MODE_STEPPER		0

struct ServStep{
	float degPrStep;
	int stepBuf{0};
	int stepSim{0};
	int svStep{0};
	float deg{0.f};
	ServStep(const float prStep) : degPrStep(prStep) {}
	const int konvStep(int step);
};

class Stp{
	enum{hintStep_length=4};
	static constexpr unsigned char hintStep[hintStep_length]={0x50,0x90,0xa0,0x60}; 
	int hintStep_idx{0};
	unsigned char pin[4];	//4 pins motor
	unsigned int speed{100};	//rotation speed per step 
	bool dirSpin_cw{true};			//rotation direcrion; CW - true
	ServStep servo;			//servo motor mode
	bool modeServo;
	void cw_spin(int p);	// spin in ClockWise direction
	void ccw_spin(int p);	// spin in CounterClockWise direction
	void motor_state_off()const;
public:
	Stp(const float prStep=1.8f,const bool mod = MODE_SERVO) : servo(prStep),modeServo(mod){}
	void toPins(const unsigned char a1,const unsigned char a2,
		const unsigned char b1,const unsigned char b2);
	void spin_direction(const bool ap){dirSpin_cw = ap;}
	void spin_speed(const unsigned int k){speed = k;}
	Stp &operator=(const int p);
};

#endif
