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

#include "Stp.hpp"
#include <Arduino.h>

/************************** ServStep *************************/
const int ServStep::konvStep(int step)
{
	bool s = false;
	if(step > deg)
	{
		while(deg < step)
		{
			svStep++;
			deg = svStep * degPrStep;
		}
		s = true;
	}
	else
	{
		while(deg-degPrStep > step)
		{	//the condition allows the limit - 1
			svStep--;
			deg = svStep * degPrStep;
		}
		if(s) { svStep++; deg = svStep * degPrStep; s = false;}		//make step closer to the target after the degree value assigned decreasing
	}
	if(abs(step - deg) > abs(step - (deg - degPrStep))) 
	{ 
		svStep--; 
		deg = svStep * degPrStep;
	}
	return svStep;
}

/************************** Stp **************************/
constexpr unsigned char Stp::hintStep[];

void Stp::toPins(const unsigned char a1,const unsigned char a2,
		const unsigned char b1,const unsigned char b2)
{
	pin[0] = a1; pin[1] = a2; pin[2] = b1; pin[3] = b2;
	for(unsigned char i=0;i<4;i++)
		pinMode(pin[i],OUTPUT);
}

void Stp::cw_spin(int p)
{
	while(p--)
	{
		if(++hintStep_idx > 3) 
			hintStep_idx = 0;
		for(byte s = 0; s < hintStep_length; s++)
			digitalWrite(pin[s],(hintStep[hintStep_idx] << s) & 0x80);
		delay(speed);
	}
	motor_state_off();	//prevent the stepper motor from getting heater
}

void Stp::ccw_spin(int p)
{
	while(p--)
	{
		if(--hintStep_idx < 0) hintStep_idx = 3;
		for(byte s = 0; s < hintStep_length; s++)
			digitalWrite(pin[s],(hintStep[hintStep_idx] << s) & 0x80);
		delay(speed);
	}
	motor_state_off();	//prevent the stepper motor from getting heater
}

void Stp::motor_state_off()const
{
	for(byte s = 0; s < hintStep_length; s++)
		digitalWrite(pin[s],LOW);
}


Stp &Stp::operator=(const int p)
{
	if(modeServo)
	{
		//convert the sum of steps into stepper from degree unit
		int konv = servo.konvStep(p);
		if(konv > servo.stepSim)
		{
			servo.stepBuf = konv - servo.stepSim;
			cw_spin(servo.stepBuf);
			servo.stepSim = konv;
		}
		else
		{
			servo.stepBuf = servo.stepSim - konv;
			ccw_spin(servo.stepBuf);
			servo.stepSim = konv;
		}
	}
	else
	{
		if(dirSpin_cw)
			cw_spin(p);
		else
			ccw_spin(p);
	}
	return *this;
}
