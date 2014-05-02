/*
  settings.h - eeprom configuration handling
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011 Sungeun K. Jeon

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

#ifndef settings_h
#define settings_h

#include <math.h>
#include <inttypes.h>
/// LETARTARE
#include "nuts_bolts.h" // N_AXIS
/// 844
#if (AXIS_T_TYPE == LINEAR)
	#define GRBL_VERSION "0.844 -> 4 axes (X, Y, Z, U)"
#else
#define GRBL_VERSION "0.844 -> 4 axes (X, Y, Z, A)"
#endif
#define GRBL_VERSION_BUILD "20140425"

// Version of the EEPROM data. Will be used to migrate existing data from older versions of Grbl
// when firmware is upgraded. Always stored in byte 0 of eeprom
#define SETTINGS_VERSION 5

// Current global settings (persisted in EEPROM from byte 1 onwards)
/// 844 : double -> float
typedef struct {
/// 844

  /// 843 : 4 -> N_AXIS,  X, Y, Z, T = U xor A
  float steps_per_mm[N_AXIS];  // linear : X, Y, Z, U
  float steps_per_degree;//[N_AXIS];  // rotary : none, none, none, A
  uint8_t microsteps;
  uint8_t pulse_microseconds;
  float default_feed_rate;
  float default_seek_rate;
  uint8_t invert_mask_stepdir;
  uint8_t invert_mask_limit;
  float mm_per_arc_segment;
  float acceleration;
  float junction_deviation;
  uint8_t spindle_pwm;
  uint32_t default_spindle;
  float max_spindle;
} settings_t;
extern settings_t settings;

// Initialize the configuration subsystem (load settings from EEPROM)
void settings_init();

// Print current settings
void settings_dump();

// Handle settings command
uint8_t settings_execute_line(char *line);

// A helper method to set new settings from command line
void settings_store_setting(int parameter, float value);

#endif
