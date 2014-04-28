/*
  pin_map.h - Pin mapping configuration file
  Part of Grbl

  Copyright (c) 2013 Sungeun K. Jeon

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

/* The pin_map.h file serves as a central pin mapping settings file for different processor
   types, i.e. AVR 328p or AVR Mega 2560. Grbl officially supports the Arduino Uno, but the
   other supplied pin mappings are supplied by users, so your results may vary. */

#ifndef pin_map_h
#define pin_map_h

// IMPORTANT: Any changes here requires a full re-compiling of the source code to propagate them.

#ifdef PIN_MAP_ARDUINO_MEGA_2560 // config.h

  // Serial port pins
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect


 /// NOTE: All step bit and direction pins must be on the same port.
  #define STEPPING_DDR      DDRA
  #define STEPPING_PORT     PORTA
  #define STEPPING_PIN      PINA
  #define X_STEP_BIT	0  // MEGA2560 Digital Pin 22
  #define Y_STEP_BIT	2  // MEGA2560 Digital Pin 24
  #define Z_STEP_BIT	4  // MEGA2560 Digital Pin 26
/// 844 : T = A xor U
  #define T_STEP_BIT	6  // MEGA2560 Digital Pin 28
  #define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<T_STEP_BIT)) // All step bits
/// <-
// Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_DDR      DDRA
  #define DIRECTION_PORT     PORTA
  #define DIRECTION_PIN      PINA
  #define X_DIRECTION_BIT	1  // MEGA2560 Digital Pin 23
  #define Y_DIRECTION_BIT	3  // MEGA2560 Digital Pin 25
  #define Z_DIRECTION_BIT	5  // MEGA2560 Digital Pin 27
/// 844
  #define T_DIRECTION_BIT	7  // MEGA2560 Digital Pin 29
  // All direction bits
  #define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<T_DIRECTION_BIT))
  // All stepping-related bits (step/direction)
  #define STEPPING_MASK (STEP_MASK | DIRECTION_MASK)

  // Define stepper driver enable/disable output pin.
  #define STEPPERS_DISABLE_DDR    DDRC
  #define STEPPERS_DISABLE_PORT   PORTC
  #define STEPPERS_DISABLE_BIT    7  // MEGA2560 Digital Pin 30
// STEPPERS_DISABLE_INVERT: Set to 0 for active high stepper disable or 1
// for active low stepper disable.
  #define STEPPERS_DISABLE_INVERT 0

 // Limit switches are active low by default. If you have active high
 // limit switches, make sure to set the invert mask in the runtime
 // configuration.
  #define LIMIT_DDR     DDRC
  #define LIMIT_PORT    PORTC
  #define LIMIT_PIN     PINC
  #define LIMIT_PULLUP
  #define X_LIMIT_BIT   6  // MEGA2560 Digital Pin 31
  #define Y_LIMIT_BIT   5  // MEGA2560 Digital Pin 32
  #define Z_LIMIT_BIT   4  // MEGA2560 Digital Pin 33
/// 844
  #define T_LIMIT_BIT   3  // MEGA2560 Digital Pin 34
// 841
  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<T_LIMIT_BIT)) // All limit bits

/// from config.h
// Comment or uncomment to determine which axes will be included in the homing
// operation. Comment out any axes you don't have limit switches on.
// not used ??
#define HOME_X
#define HOME_Y
#define HOME_Z
#define HOME_T

    // Define spindle enable and spindle direction output pins.
    /// 0.84 = 0.9d
  #define SPINDLE_ENABLE_DDR   DDRH
  #define SPINDLE_ENABLE_PORT  PORTH
  #define SPINDLE_ENABLE_BIT   3 // MEGA2560 Digital Pin 6
///---> LETARTARE 16/04/2014
// SPINDLE_ENABLE_ACTIVE: Set to 0 for active low spindle enable or 1
// for active high enable.
#define SPINDLE_ENABLE_ACTIVE  0
///<---
  #define SPINDLE_DIRECTION_DDR   DDRE
  #define SPINDLE_DIRECTION_PORT  PORTE
// 0.9d
//  #define SPINDLE_DIRECTION_BIT   3 // MEGA2560 Digital Pin 5
#define SPINDLE_DIRECTION_BIT 1  //  MEGA2560 Digital Pin 36
///---> LETARTARE 16/04/2014
// SPINDLE_DIRECTION_ACTIVE: Set to 0 for active low spindle direction or 1
// for active high enable.
#define SPINDLE_DIRECTION_ACTIVE  1
///<---

// Define flood and mist coolant enable output pins.
  // NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
  // a later date if flash and memory space allows.
 #define COOLANT_FLOOD_DDR 	DDRC
 #define COOLANT_FLOOD_PORT 	PORTC
 #define COOLANT_FLOOD_BIT	0	// MEGA2560 Digital Pin 37
///---> LETARTARE 16/04/2014
// COOLANT_FLOOD_ACTIVE: Set to 0 for active low flood enable or 1
// for active high enable.
 #define COOLANT_FLOOD_ACTIVE  0
///<---

 #define ENABLE_M7 // ENABLED BY DEFAULT: Comment out to disable
 #ifdef ENABLE_M7
 #define COOLANT_MIST_DDR   	DDRC
 #define COOLANT_MIST_PORT   PORTC
 #define COOLANT_MIST_BIT  	2 // MEGA2560 Digital Pin 35
//---> LETARTARE 16/04/2014
// COOLANT_MIST_ACTIVE: Set to 0 for active low mist enable or 1
// for active high enable.
 #define COOLANT_MIST_ACTIVE  0
#endif

// 0.8c  not used here  !!
  // NOTE: All pinouts pins must be on the same port
  #define PINOUT_DDR       DDRK
  #define PINOUT_PIN       PINK
  #define PINOUT_PORT      PORTK
  // => TODO
  #define PIN_RESET        0  // MEGA2560 Analog Pin 8
  #define PIN_FEED_HOLD    1  // MEGA2560 Analog Pin 9
  #define PIN_CYCLE_START  2  // MEGA2560 Analog Pin 10
  #define PINOUT_INT       PCIE2  // Pin change interrupt enable pin
  #define PINOUT_INT_vect  PCINT2_vect
  #define PINOUT_PCMSK     PCMSK2 // Pin change interrupt register
  #define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))
  // <=

#endif

/*
#ifdef PIN_MAP_ARDUINO_UNO // AVR 328p, Officially supported by Grbl.
  // Serial port pins
  #define SERIAL_RX USART_RX_vect
  #define SERIAL_UDRE USART_UDRE_vect

  // NOTE: All step bit and direction pins must be on the same port.
  #define STEPPING_DDR       DDRD
  #define STEPPING_PORT      PORTD
  #define X_STEP_BIT         2  // Uno Digital Pin 2
  #define Y_STEP_BIT         3  // Uno Digital Pin 3
  #define Z_STEP_BIT         4  // Uno Digital Pin 4
  #define X_DIRECTION_BIT    5  // Uno Digital Pin 5
  #define Y_DIRECTION_BIT    6  // Uno Digital Pin 6
  #define Z_DIRECTION_BIT    7  // Uno Digital Pin 7
  #define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
  #define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
  #define STEPPING_MASK (STEP_MASK | DIRECTION_MASK) // All stepping-related bits (step/direction)

  #define STEPPERS_DISABLE_DDR    DDRB
  #define STEPPERS_DISABLE_PORT   PORTB
  #define STEPPERS_DISABLE_BIT    0  // Uno Digital Pin 8
  #define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

  // NOTE: All limit bit pins must be on the same port
  #define LIMIT_DDR       DDRB
  #define LIMIT_PIN       PINB
  #define LIMIT_PORT      PORTB
  #define X_LIMIT_BIT     1  // Uno Digital Pin 9
  #define Y_LIMIT_BIT     2  // Uno Digital Pin 10
  #define Z_LIMIT_BIT     3  // Uno Digital Pin 11
  #define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect  PCINT0_vect
  #define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

  #define SPINDLE_ENABLE_DDR   DDRB
  #define SPINDLE_ENABLE_PORT  PORTB
  #define SPINDLE_ENABLE_BIT   4  // Uno Digital Pin 12

  #define SPINDLE_DIRECTION_DDR   DDRB
  #define SPINDLE_DIRECTION_PORT  PORTB
  #define SPINDLE_DIRECTION_BIT   5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)

  #define COOLANT_FLOOD_DDR   DDRC
  #define COOLANT_FLOOD_PORT  PORTC
  #define COOLANT_FLOOD_BIT   3  // Uno Analog Pin 3

  // NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
  // a later date if flash and memory space allows.
  // #define ENABLE_M7  // Mist coolant disabled by default. Uncomment to enable.
  #ifdef ENABLE_M7
    #define COOLANT_MIST_DDR   DDRC
    #define COOLANT_MIST_PORT  PORTC
    #define COOLANT_MIST_BIT   4 // Uno Analog Pin 4
  #endif

  // NOTE: All pinouts pins must be on the same port
  #define PINOUT_DDR       DDRC
  #define PINOUT_PIN       PINC
  #define PINOUT_PORT      PORTC
  #define PIN_RESET        0  // Uno Analog Pin 0
  #define PIN_FEED_HOLD    1  // Uno Analog Pin 1
  #define PIN_CYCLE_START  2  // Uno Analog Pin 2
  #define PINOUT_INT       PCIE1  // Pin change interrupt enable pin
  #define PINOUT_INT_vect  PCINT1_vect
  #define PINOUT_PCMSK     PCMSK1 // Pin change interrupt register
  #define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))
#endif
*/
/*
#ifdef PIN_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and paste one of the default pin map
  // settings above and modify it to your needs. Then, make sure the defined name is also
  // changed in the config.h file.
#endif
*/

#endif
