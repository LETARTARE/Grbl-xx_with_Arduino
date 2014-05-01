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

#ifdef DEFAULTS_LETARTARE

/// 845
//==============================================================================
/// This is where you define the type of the fourth axis T
/// 	- T = axis U, V, W linear or  axis A, B, C rotary
/// 	- The axis T uses MEGA2560 Digital pin 28

  #define LINEAR 0		//  0 -> linear T = U or V or W
  #define ROTARY 1		//  1 -> rotary T = A or B or C
/// ====> You must choose only one type, but not both  <====
  //#define AXIS_T_TYPE 	LINEAR  	//  0 -> linear
  #define AXIS_T_TYPE 	ROTARY 		//  1 -> rotary
  // Checking the definition of "AXIS_T_TYPE"
  #ifndef AXIS_T_TYPE
     #error "The macro "AXIS_T_TYPE" is not defined"
  #endif

/// axis choice
 #if AXIS_T_TYPE == LINEAR
	#define AXIS_U   4
	#define AXIS_V   5
	#define AXIS_W   6
	// linear axis
	#define AXIS_T 	AXIS_U  /// ==> You must choose your fourth linear axis  <==
 #elif AXIS_T_TYPE == ROTARY
	#define AXIS_A   7
	#define AXIS_B   8
	#define AXIS_C   9
	// rotary axis
	#define AXIS_T 	AXIS_A  /// ==> You must choose your rotary fourth axis  <==
 #else
	/// -> (X, Y, Z)
 #endif

 // Checking the definition of "AXIS_T"
 #ifndef AXIS_T
     #error "The macro "AXIS_T" is not defined"
  #endif

//==============================================================================

//==============================================================================
/// This is where you define the common characteristics of
///  	- stepper motors
///  	- power interface
///  	- pitch screw for linear axis
///  	- ratio_table for rotary axis

  ///  step_per_revolution = number of motor steps per revolution
  #define USER_STEP_PER_REVOLUTION  200
  /// board TB6560 -> 2 탎teps
  #define USER_MICROSTEPS 2
  ///  pitch_screw = pitch of screw
  #define USER_PITCH_SCREW   4   // 4mm for all linear axes
  #define USER_STEP_MM  (USER_STEP_PER_REVOLUTION/USER_PITCH_SCREW)
  ///  ratio_table  =  the worm gear ratio
  #define USER_RATIO_TABLE  90   // for rotary axis
//==============================================================================
/// <==

// Grbl generic default settings. Should work across different machines.
  #define DEFAULT_X_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS) //  -> 1 탎tep = 0.01 mm
  #define DEFAULT_Y_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS)
  #define DEFAULT_Z_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS)
/// =====> 845  :  T in  U, if A, B, C -> mm = degree
#define DEFAULT_T_STEPS_PER_MM (USER_STEP_MM*USER_MICROSTEPS)
  // user values
  // calculated value Grbl = ratio_table*step_per_revolution/360
  #define USER_TABLE   ((USER_RATIO_TABLE*USER_STEP_PER_REVOLUTION)/360.0)
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
/*
#ifdef DEFAULTS_GENERIC
  // Grbl generic default settings. Should work across different machines.
  #define DEFAULT_X_STEPS_PER_MM 250.0
  #define DEFAULT_Y_STEPS_PER_MM 250.0
  #define DEFAULT_Z_STEPS_PER_MM 250.0
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_MM_PER_ARC_SEGMENT 0.1
  #define DEFAULT_RAPID_FEEDRATE 500.0 // mm/min
  #define DEFAULT_FEEDRATE 250.0
  #define DEFAULT_ACCELERATION (10.0*60*60) // 10 mm/min^2
  #define DEFAULT_JUNCTION_DEVIATION 0.05 // mm
  #define DEFAULT_STEPPING_INVERT_MASK ((1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT))
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

#ifdef DEFAULTS_SHERLINE_5400
  // Description: Sherline 5400 mill with three NEMA 23 Keling  KL23H256-21-8B 185 oz-in stepper motors,
  // driven by three Pololu A4988 stepper drivers with a 30V, 6A power supply at 1.5A per winding.
  #define MICROSTEPS 2
  #define STEPS_PER_REV 200.0
  #define MM_PER_REV (0.050*MM_PER_INCH) // 0.050 inch/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Y_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Z_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_MM_PER_ARC_SEGMENT 0.1
  #define DEFAULT_RAPID_FEEDRATE 635.0 // mm/min (25ipm)
  #define DEFAULT_FEEDRATE 254.0 // mm/min (10ipm)
  #define DEFAULT_ACCELERATION 50.0*60*60 // 50 mm/min^2
  #define DEFAULT_JUNCTION_DEVIATION 0.05 // mm
  #define DEFAULT_STEPPING_INVERT_MASK ((1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT))
  #define DEFAULT_REPORT_INCHES 1 // false
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

#ifdef DEFAULTS_SHAPEOKO
  // Description: Shapeoko CNC mill with three NEMA 17 stepper motors, driven by Synthetos
  // grblShield with a 24V, 4.2A power supply.
  #define MICROSTEPS_XY 8
  #define STEP_REVS_XY 400
  #define MM_PER_REV_XY (0.08*18*MM_PER_INCH) // 0.08 in belt pitch, 18 pulley teeth
  #define MICROSTEPS_Z 2
  #define STEP_REVS_Z 400
  #define MM_PER_REV_Z 1.250 // 1.25 mm/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_MM_PER_ARC_SEGMENT 0.1
  #define DEFAULT_RAPID_FEEDRATE 1000.0 // mm/min
  #define DEFAULT_FEEDRATE 250.0
  #define DEFAULT_ACCELERATION (15.0*60*60) // 15 mm/min^2
  #define DEFAULT_JUNCTION_DEVIATION 0.05 // mm
  #define DEFAULT_STEPPING_INVERT_MASK ((1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT))
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
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-255)
  #define DEFAULT_DECIMAL_PLACES 3
  #define DEFAULT_N_ARC_CORRECTION 25
#endif

#ifdef DEFAULTS_ZEN_TOOLWORKS_7x7
  // Description: Zen Toolworks 7x7 mill with three Shinano SST43D2121 65oz-in NEMA 17 stepper motors.
  // Leadscrew is different from some ZTW kits, where most are 1.25mm/rev rather than 8.0mm/rev here.
  // Driven by 30V, 6A power supply and TI DRV8811 stepper motor drivers.
  #define MICROSTEPS 8
  #define STEPS_PER_REV 200.0
  #define MM_PER_REV 8.0 // 8 mm/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Y_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Z_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_MM_PER_ARC_SEGMENT 0.1
  #define DEFAULT_RAPID_FEEDRATE 2500.0 // mm/min
  #define DEFAULT_FEEDRATE 1000.0 // mm/min
  #define DEFAULT_ACCELERATION 150.0*60*60 // 150 mm/min^2
  #define DEFAULT_JUNCTION_DEVIATION 0.05 // mm
  #define DEFAULT_STEPPING_INVERT_MASK (1<<Y_DIRECTION_BIT)
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_AUTO_START 1 // true
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_RAPID_FEEDRATE 500.0 // mm/min
  #define DEFAULT_HOMING_FEEDRATE 50.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 100 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-255)
  #define DEFAULT_DECIMAL_PLACES 3
  #define DEFAULT_N_ARC_CORRECTION 25
#endif
*/


#endif
