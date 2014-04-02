/*
  spindle_control.c - spindle control methods
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2012 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "spindle_control.h"
#include "settings.h"
#include "motion_control.h"
#include "config.h"
#include "planner.h"
#include "stepper.h"

#include <stdint.h>

static uint8_t current_direction;

void spindle_init()
{
  current_direction = 0;
  SPINDLE_ENABLE_DDR |= (1<<SPINDLE_ENABLE_BIT);
  SPINDLE_DIRECTION_DDR |= (1<<SPINDLE_DIRECTION_BIT);  
  spindle_stop();
}

void spindle_stop()
{
  SPINDLE_ENABLE_PORT &= ~(1<<SPINDLE_ENABLE_BIT);
}

void spindle_run(int8_t direction, uint16_t rpm) 
{
  if (direction != current_direction) {
    plan_synchronize();
    if (direction) {
      if(direction > 0) {
        SPINDLE_DIRECTION_PORT &= ~(1<<SPINDLE_DIRECTION_BIT);
      } else {
        SPINDLE_DIRECTION_PORT |= 1<<SPINDLE_DIRECTION_BIT;
      }
      SPINDLE_ENABLE_PORT |= 1<<SPINDLE_ENABLE_BIT;
    } else {
      spindle_stop();     
    }
    current_direction = direction;
    }
if (settings.spindle_pwm == 1) {
  if (rpm > settings.max_spindle) {
    rpm = settings.max_spindle;
    }
  if (direction == 0) {
    rpm = 0;
    OCR4A = 0;
    TCCR4A = 0; //reset clock values
    TCCR4B = 0; //reset clock values
    }  
  else if (rpm > 0 ) {
    TCCR4A = 0; //reset clock values
    TCCR4B = 0; //reset clock values
    TCCR4A = (1<<COM4A1) | (1<<WGM42) | (1<<WGM41) | (1<<WGM40); //10 bit Fast PWM
    TCCR4B = (1<<CS41); //set prescaler to 8
    OCR4A = rpm / settings.max_spindle * 1023;
    }
  else {
    TCCR4A = 0; //reset clock values
    TCCR4B = 0; //reset clock values
    TCCR4A = (1<<COM4A1) | (1<<WGM42) | (1<<WGM41) | (1<<WGM40); //10 bit Fast PWM
    TCCR4B = (1<<CS41); //set prescaler to 8
    OCR4A = settings.default_spindle / settings.max_spindle * 1023;
    }
}     
}