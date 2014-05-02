/*
  settings.c - eeprom configuration handling
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

#include <avr/io.h>
#include <math.h>
#include "nuts_bolts.h"
#include "settings.h"
#include "eeprom.h"
#include "print.h"
#include <avr/pgmspace.h>
#include "protocol.h"
#include "stepper.h"
#include "spindle_control.h"
#include "coolant_control.h"

settings_t settings;

// Version 1 outdated settings record
typedef struct {
//// 843 : 4 -> N_AXIS
  double steps_per_mm[N_AXIS];
/// 845
  double steps_per_degree;
  uint8_t microsteps;
  uint8_t pulse_microseconds;
  double default_feed_rate;
  double default_seek_rate;
  uint8_t invert_mask;
  double mm_per_arc_segment;
} settings_v1_t;

void settings_reset() {
  settings.steps_per_mm[X_AXIS] = DEFAULT_X_STEPS_PER_MM;
  settings.steps_per_mm[Y_AXIS] = DEFAULT_Y_STEPS_PER_MM;
  settings.steps_per_mm[Z_AXIS] = DEFAULT_Z_STEPS_PER_MM;
/// 844 : axis T
#if (AXIS_T_TYPE == LINEAR)
   settings.steps_per_mm[T_AXIS] = DEFAULT_T_STEPS_PER_MM;
#else
   settings.steps_per_degree = DEFAULT_T_STEPS_PER_DEGREE;
#endif

  settings.pulse_microseconds = DEFAULT_STEP_PULSE_MICROSECONDS;
  settings.default_feed_rate = DEFAULT_FEEDRATE;
  settings.default_seek_rate = DEFAULT_RAPID_FEEDRATE;
  settings.acceleration = DEFAULT_ACCELERATION;
  settings.mm_per_arc_segment = DEFAULT_MM_PER_ARC_SEGMENT;
  settings.invert_mask_stepdir = DEFAULT_STEPPING_INVERT_MASK;
  settings.invert_mask_limit = DEFAULT_LIMIT_INVERT_MASK;
  settings.junction_deviation = DEFAULT_JUNCTION_DEVIATION;
  settings.spindle_pwm = SPINDLE_PWM;
  settings.default_spindle = DEFAULT_SPINDLE_SPEED;
  settings.max_spindle = MAX_SPINDLE_SPEED;
}

void settings_dump() {
  printPgmString(PSTR("$VERSION = "));
  printPgmString(PSTR(GRBL_VERSION " " GRBL_AXIS));
  printPgmString(PSTR("\r\n"));

  printPgmString(PSTR("$0 = "));
  printFloat(settings.steps_per_mm[X_AXIS]);
  printPgmString(PSTR(" (steps/mm x)\r\n"));

  printPgmString(PSTR("$1 = "));
  printFloat(settings.steps_per_mm[Y_AXIS]);
  printPgmString(PSTR(" (steps/mm y)\r\n"));

  printPgmString(PSTR("$2 = "));
  printFloat(settings.steps_per_mm[Z_AXIS]);
  printPgmString(PSTR(" (steps/mm z)\r\n"));

/// 845 : axis X, Y, Z, U, V, W
/// axis U, V, W
#if (AXIS_T_TYPE == LINEAR)
  printPgmString(PSTR("$3 = "));
  printFloat(settings.steps_per_mm[T_AXIS]);
#if AXIS_T == AXIS_U
	printPgmString(PSTR(" (steps/mm u)\r\n"));
#elif AXIS_T == AXIS_V
	printPgmString(PSTR(" (steps/mm v)\r\n"));
#elif AXIS_T == AXIS_W
	printPgmString(PSTR(" (steps/mm w)\r\n"));
#endif

#else
/// axis A, B, C
  printPgmString(PSTR("$3 = "));
  printFloat(settings.steps_per_degree);
#if AXIS_T == AXIS_A
	printPgmString(PSTR(" (steps/deg. a)\r\n"));
#elif AXIS_T == AXIS_B
	printPgmString(PSTR(" (steps/deg. b)\r\n"));
#elif AXIS_T == AXIS_C
	printPgmString(PSTR(" (steps/deg. C)\r\n"));
#endif

#endif

  printPgmString(PSTR("$4 = "));
  printInteger(settings.pulse_microseconds);
  printPgmString(PSTR(" (microseconds step pulse)\r\n"));

  printPgmString(PSTR("$5 = "));
  printFloat(settings.default_feed_rate);
  printPgmString(PSTR(" (mm/min default feed rate)\r\n"));

  printPgmString(PSTR("$6 = "));
  printFloat(settings.default_seek_rate);
  printPgmString(PSTR(" (mm/min default seek rate)\r\n"));

  printPgmString(PSTR("$7 = "));
  printFloat(settings.mm_per_arc_segment);
  printPgmString(PSTR(" (mm/arc segment)\r\n"));

  printPgmString(PSTR("$8 = "));
  printInteger(settings.invert_mask_stepdir);
  printPgmString(PSTR(" (step port invert mask. binary = "));
  print_uint8_base2(settings.invert_mask_stepdir);
  printPgmString(PSTR(")\r\n"));

  printPgmString(PSTR("$9 = "));
  printInteger(settings.invert_mask_limit);
  printPgmString(PSTR(" (step port invert mask limit. binary = "));
  print_uint8_base2(settings.invert_mask_limit);
  printPgmString(PSTR(")\r\n"));

  printPgmString(PSTR("$10 = "));
  printFloat(settings.acceleration/(60*60));
  printPgmString(PSTR(" (acceleration in mm/sec^2)\r\n"));

  printPgmString(PSTR("$11 = "));
  printFloat(settings.junction_deviation);
  printPgmString(PSTR(" (cornering junction deviation in mm)\r\n"));

  printPgmString(PSTR("$12 = "));
  printInteger(settings.spindle_pwm);
  printPgmString(PSTR(" (PWM on Spindle: 0 = disabled, 1 = enabled)\r\n"));

  printPgmString(PSTR("$13 = "));
  printFloat(settings.default_spindle);
  printPgmString(PSTR(" (default spindle speed in RPM)\r\n"));

  printPgmString(PSTR("$14 = "));
  printFloat(settings.max_spindle);
  printPgmString(PSTR(" (maximum spindle speed in RPM)\r\n"));

  printPgmString(PSTR("$1000 = "));
  printInteger(st_is_enabled());
  printPgmString(PSTR(" (steppers: 0 = disabled, 1 = enabled)\r\n"));

  printPgmString(PSTR("\r\n'$x=value' to set parameter or just '$' to dump current settings\r\n"));
}

// Parameter lines are on the form '$4=374.3' or '$' to dump current settings
uint8_t settings_execute_line(char *line) {
  uint8_t char_counter = 1;
  double parameter, value;
  if(line[0] != '$') {
    return(STATUS_UNSUPPORTED_STATEMENT);
  }
  if(line[char_counter] == 0) {
    settings_dump(); return(STATUS_OK);
  }
  if(!read_double(line, &char_counter, &parameter)) {
    return(STATUS_BAD_NUMBER_FORMAT);
  };
  if(line[char_counter++] != '=') {
    return(STATUS_UNSUPPORTED_STATEMENT);
  }
  if(!read_double(line, &char_counter, &value)) {
    return(STATUS_BAD_NUMBER_FORMAT);
  }
  if(line[char_counter] != 0) {
    return(STATUS_UNSUPPORTED_STATEMENT);
  }
  settings_store_setting(parameter, value);
  return(STATUS_OK);
}

void write_settings() {
  eeprom_put_char(0, SETTINGS_VERSION);
  memcpy_to_eeprom_with_checksum(1, (char*)&settings, sizeof(settings_t));
}

int read_settings() {
  // Check version-byte of eeprom
  uint8_t version = eeprom_get_char(0);

  if (version == SETTINGS_VERSION) {
    // Read settings-record and check checksum
    if (!(memcpy_from_eeprom_with_checksum((char*)&settings, 1, sizeof(settings_t)))) {
      return(false);
    }
  }
  else
  if (version == 1) {
    // Migrate from settings version 1
    if (!(memcpy_from_eeprom_with_checksum((char*)&settings, 1, sizeof(settings_v1_t)))) {
      return(false);
    }
    settings.acceleration = DEFAULT_ACCELERATION;
    settings.junction_deviation = DEFAULT_JUNCTION_DEVIATION;
//     settings.auto_start = DEFAULT_AUTO_START;
    write_settings();
  }
  else
  if ((version == 2) || (version == 3)) {
    // Migrate from settings version 2 and 3
    if (!(memcpy_from_eeprom_with_checksum((char*)&settings, 1, sizeof(settings_t)))) {
      return(false);
    }
    if (version == 2) {
        settings.junction_deviation = DEFAULT_JUNCTION_DEVIATION;
    }
    settings.acceleration *= 3600; // Convert to mm/min^2 from mm/sec^2
//     settings.auto_start = DEFAULT_AUTO_START;
    write_settings();
  }
  else
  if (version == 4) {
     // Migrate from settings version 4
     if (!(memcpy_from_eeprom_with_checksum((char*)&settings, 1, sizeof(settings_t)))) {
       return(false);
     }
     //settings.auto_start = DEFAULT_AUTO_START;
     settings.spindle_pwm = SPINDLE_PWM;
     settings.default_spindle = DEFAULT_SPINDLE_SPEED;
     settings.max_spindle = MAX_SPINDLE_SPEED;
     write_settings();
  }
  else
    return false;

  return true;
}

// A helper method to set settings from command line
void settings_store_setting(int parameter, double value) {
  switch(parameter) {
	case 0: case 1: case 2:   // X, Y, Z
        if (value <= 0.0) {
          printPgmString(PSTR("Steps/mm must be > 0.0\r\n"));
          return;
        }
        settings.steps_per_mm[parameter] = value;
        break;
    case 3 :   // axe T : linear -> U or V or W,  rotary -> A or B or C
		if (value <= 0.0) {
	#if AXIS_T_TYPE == LINEAR
			printPgmString(PSTR("Steps/mm must be > 0.0\r\n"));
    #else
			printPgmString(PSTR("Steps/degree must be > 0.0\r\n"));
    #endif
          return;
        }
    #if AXIS_T_TYPE == LINEAR
        settings.steps_per_mm[parameter] = value;
    #else
		settings.steps_per_degree = value;
    #endif

		break;
    case 4:
        if (value < 3) {
            printPgmString(PSTR("Step pulse must be >= 3 microseconds\r\n"));
            return;
        }
        settings.pulse_microseconds = round(value);
        break;
    case 5:
        settings.default_feed_rate = value;
        break;
    case 6:
        settings.default_seek_rate = value;
        break;
    case 7:
        settings.mm_per_arc_segment = value;
        break;
    case 8:
        settings.invert_mask_stepdir = trunc(value);
        break;
    case 9:
        settings.invert_mask_limit = trunc(value);
        break;
    case 10:
        settings.acceleration = value*60*60;
        break; // Convert to mm/min^2 for grbl internal use.
    case 11:
        settings.junction_deviation = fabs(value);
        break;
    case 12:
        settings.spindle_pwm = value;
        break;
    case 13:
        settings.default_spindle = value;
        break;
    case 14:
        settings.max_spindle = value;
        break;
    case 1000:
    	value ? st_enable(): st_disable();
    	if (!value) {
    		coolant_stop();
    		spindle_stop();
    	}
    	return;
        break;
    default:
      printPgmString(PSTR("Unknown parameter\r\n"));
      return;
  }
  write_settings();
  printPgmString(PSTR("Stored new setting\r\n"));
}

// Initialize the config subsystem
void settings_init() {
  if(!read_settings()) {
    printPgmString(PSTR("Warning: Failed to read EEPROM settings. Using defaults.\r\n"));
    settings_reset();
    write_settings();
    settings_dump();
  }
}
