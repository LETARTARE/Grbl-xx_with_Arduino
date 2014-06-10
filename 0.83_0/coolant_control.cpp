/*
  coolant_control.c - coolant control methods
  Part of Grbl

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

#include "coolant_control.h"
#include "settings.h"
#include "config.h"
#include "planner.h"

#include <avr/io.h>

static uint8_t current_coolant_mode;

void coolant_init()
{
  current_coolant_mode = COOLANT_DISABLE;
  #ifdef ENABLE_M7
    // Configure as output pin.
    COOLANT_MIST_DDR |= (1 << COOLANT_MIST_BIT);
  #endif
  // Configure as output pin.
  COOLANT_FLOOD_DDR |= (1 << COOLANT_FLOOD_BIT);
  coolant_stop();
}

void coolant_stop()
{
  #ifdef ENABLE_M7
///---> LETARTARE 16/04/2014
     #if COOLANT_MIST_ACTIVE == 1
      // Set pin to low to stop.
        COOLANT_MIST_PORT &= ~(1 << COOLANT_MIST_BIT);
     #else
     // Set pin to high to stop.
        COOLANT_MIST_PORT |= (1 << COOLANT_MIST_BIT);
     #endif
  #endif
  #if COOLANT_FLOOD_ACTIVE == 1
    // Set pin to low to stop.
    COOLANT_FLOOD_PORT &= ~(1 << COOLANT_FLOOD_BIT);
  #else
    // Set pin to high to stop.
    COOLANT_FLOOD_PORT |= (1 << COOLANT_FLOOD_BIT);
  #endif
///<---
}


void coolant_run(uint8_t mode)
{
  if (mode != current_coolant_mode)
  { 
    plan_synchronize(); // Ensure coolant turns on when specified in program.
    if (mode == COOLANT_FLOOD_ENABLE) {
///---> LETARTARE 16/04/2014
    #if COOLANT_FLOOD_ACTIVE == 1
        // Set pin to high to run.
        COOLANT_FLOOD_PORT |= (1 << COOLANT_FLOOD_BIT);
    #else
        // Set pin to low to run.
        COOLANT_FLOOD_PORT &= ~(1 << COOLANT_FLOOD_BIT);
    #endif
///<---
    #ifdef ENABLE_M7  
    }
    else
    if (mode == COOLANT_MIST_ENABLE) {
///---> LETARTARE 16/04/2014
        #if COOLANT_MIST_ACTIVE == 1
        // Set pin to high to run.
        COOLANT_MIST_PORT |= (1 << COOLANT_MIST_BIT);
        #else
        // Set pin to low to run.
        COOLANT_MIST_PORT &= ~(1 << COOLANT_MIST_BIT);
        #endif
///<---
    #endif
    }
    else {
      coolant_stop();
    }
    current_coolant_mode = mode;
  }
}
