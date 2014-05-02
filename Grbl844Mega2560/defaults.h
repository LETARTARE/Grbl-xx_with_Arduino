/*
  defaults.h - defaults settings configuration file
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

/* The defaults.h file serves as a central default settings file for different machine
   types, from DIY CNC mills to CNC conversions of off-the-shelf machines. The settings
   here are supplied by users, so your results may vary. However, this should give you
   a good starting point as you get to know your machine and tweak the settings for your
   our nefarious needs. */

#ifndef defaults_h
#define defaults_h

// IMPORTANT: Any changes here requires a full re-compiling of the source code to propagate them.

/// ==> 843 25-04-2014 axes X, Y, Z, A  (rotary axis)
#ifdef DEFAULTS_LETARTARE

/// 844 : T = axis U linear or  T = axis A rotary
//the axis A  and the axis  A on the same pin
// One must choose only one or the other, can not have both them
  #define LINEAR 0
  #define ROTARY 1
 // #define AXIS_T_TYPE LINEAR //  0 -> linear T = U
  #define AXIS_T_TYPE ROTARY //   1 -> rotary T = A

#if ((AXIS_T_TYPE  != LINEAR) && (AXIS_T_TYPE  != ROTARY))
   #error "Macro 'AXIS_T_TYPE' is not defined"
#endif

// board TB6560 -> 2 탎teps
  #define USER_MICROSTEPS 4
/// ==> 843
  // step_per_revolution = number of motor steps per revolution
  #define USER_STEP_PER_REVOLUTION  200.0
  // pitch_screw  = pitch of screw
  #define USER_PITCH_SCREW   4.0   // pitch of the screw = 4mm for all axes
  #define USER_STEP_MM  (USER_STEP_PER_REVOLUTION/USER_PITCH_SCREW)
/// <==

// Grbl generic default settings. Should work across different machines.
  #define DEFAULT_X_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS) //  -> 1 탎tep = 0.01 mm
  #define DEFAULT_Y_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS)
  #define DEFAULT_Z_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS)
/// =====> 844  :  T = A xor U, if A -> mm = degree
#define DEFAULT_T_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS)
  // user values
  // ratio_table  =  the worm gear ratio
  #define USER_RATIO_TABLE  90
  #define USER_TABLE   ((USER_RATIO_TABLE*USER_STEP_PER_REVOLUTION)/360.0)
  // calculated value Grbl = ratio_table*step_per_revolution/360
  // STEPS_PER_DEGREE = (ratio_table*step_per_revolution/360)*MICROSTEPS)
  // 탎tep/degree   1 탎tep = 0,01 �
  #define DEFAULT_T_STEPS_PER_DEGREE (USER_TABLE*USER_MICROSTEPS)
/// <=====

  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_MM_PER_ARC_SEGMENT 0.1
  #define DEFAULT_RAPID_FEEDRATE 1500.0 // mm/min
  #define DEFAULT_FEEDRATE 750.0
  #define DEFAULT_ACCELERATION (DEFAULT_FEEDRATE*60*60/10.0) // 10 mm/min^2
  #define DEFAULT_JUNCTION_DEVIATION 0.05 // mm
// ==> 844 add  axis T
  #define DEFAULT_STEPPING_INVERT_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<T_STEP_BIT))

  #define DEFAULT_LIMIT_INVERT_MASK 0 // active-low endstops by default
  // #define DEFAULT_AUTO_START 1 // Boolean
  #define SPINDLE_PWM 0 // Spindle PWM NOT Active as default
  #define DEFAULT_SPINDLE_SPEED 300 // RPM
  #define MAX_SPINDLE_SPEED 1000 // RPM
// <==

/// ==> 0.842 : 0.8c not use actually !!  to introduce in 0.843 ?
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_AUTO_START 1 // true
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_RAPID_FEEDRATE 250.0 // mm/min
  #define DEFAULT_HOMING_FEEDRATE 25.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 100 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-255)
  #define DEFAULT_DECIMAL_PLACES 3
  #define DEFAULT_N_ARC_CORRECTION 25
#endif
/// <==

#endif
