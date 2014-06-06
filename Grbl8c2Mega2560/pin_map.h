/*
  pin_map.h - Pin mapping configuration file
  Part of Grbl

  Copyright (c) 2013 Sungeun K. Jeon

   The MIT License (MIT)

  GRBL(tm) - Embedded CNC g-code interpreter and motion-controller
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011-2013 Sungeun K. Jeon

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/* The pin_map.h file serves as a central pin mapping settings file for different processor
   types, i.e. AVR 328p or AVR Mega 2560. Grbl officially supports the Arduino Uno, but the
   other supplied pin mappings are supplied by users, so your results may vary. */

#ifndef pin_map_h
#define pin_map_h

#include "config.h"    // PIN_MAP_ARDUINO_MEGA_2560

#ifdef PIN_MAP_ARDUINO_UNO // AVR 328p, Officially supported by Grbl.
/// 8c2
#ifdef AXIS_T_TYPE
    #error "The macro "AXIS_T_TYPE" is defined"
#endif

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


#ifdef PIN_MAP_ARDUINO_MEGA_2560

#ifndef AXIS_T_TYPE
    #error "The macro "AXIS_T_TYPE" is not defined in 'config.h' !"
#endif

  // Serial port pins
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect

  // NOTE: All step bit and direction pins must be on the same port.
  #define STEPPING_DDR      DDRA
  #define STEPPING_PORT     PORTA
  #define STEPPING_PIN      PINA
  #define X_STEP_BIT        0 // MEGA2560 Digital Pin 22
  #define Y_STEP_BIT        2 // MEGA2560 Digital Pin 24
  #define Z_STEP_BIT        4 // MEGA2560 Digital Pin 26
/// 8c1
  #define T_STEP_BIT        6 // MEGA2560 Digital Pin 28

  #define X_DIRECTION_BIT   1 // MEGA2560 Digital Pin 23
  #define Y_DIRECTION_BIT   3 // MEGA2560 Digital Pin 25
  #define Z_DIRECTION_BIT   5 // MEGA2560 Digital Pin 27
/// 8c1
  #define T_DIRECTION_BIT   7 // MEGA2560 Digital Pin 29
  // All step bits
 #define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<T_STEP_BIT) )
// All direction bits
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT) |(1<<T_DIRECTION_BIT))
/// <--
  // All stepping-related bits (step/direction)
  #define STEPPING_MASK (STEP_MASK | DIRECTION_MASK)
/// 8c1
   // Define stepper driver enable/disable output pin.
	  #define STEPPERS_DISABLE_DDR    DDRC
	  #define STEPPERS_DISABLE_PORT   PORTC
	  #define STEPPERS_DISABLE_BIT    7  // MEGA2560 Digital Pin 30
	  // STEPPERS_DISABLE_INVERT: Set to 0 for active high stepper disable or 1
	  // for active low stepper disable.
	  #define STEPPERS_DISABLE_INVERT 0
	  #define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)
/// <---
  // NOTE: All limit bit pins must be on the same port
  #define LIMIT_DDR       DDRB
  #define LIMIT_PORT      PORTB
  #define LIMIT_PIN       PINB
  #define X_LIMIT_BIT     4 // MEGA2560 Digital Pin 10
  #define Y_LIMIT_BIT     5 // MEGA2560 Digital Pin 11
  #define Z_LIMIT_BIT     6 // MEGA2560 Digital Pin 12
/// 8c1
  #define T_LIMIT_BIT     3 // MEGA2560 Digital Pin 9

  #define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect  PCINT0_vect
  #define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT) |(1<<T_LIMIT_BIT)) // All limit bits

  #define SPINDLE_ENABLE_DDR   DDRC
  #define SPINDLE_ENABLE_PORT  PORTC
  #define SPINDLE_ENABLE_BIT   2 // MEGA2560 Digital Pin 35

  #define SPINDLE_DIRECTION_DDR   DDRC
  #define SPINDLE_DIRECTION_PORT  PORTC
  #define SPINDLE_DIRECTION_BIT   1 // MEGA2560 Digital Pin 36

  #define COOLANT_FLOOD_DDR   DDRC
  #define COOLANT_FLOOD_PORT  PORTC
  #define COOLANT_FLOOD_BIT   0 // MEGA2560 Digital Pin 37

  // #define ENABLE_M7  // Mist coolant disabled by default. Uncomment to enable.
  #ifdef ENABLE_M7
    #define COOLANT_MIST_DDR   DDRC
    #define COOLANT_MIST_PORT  PORTC
    #define COOLANT_MIST_BIT   3 // MEGA2560 Digital Pin 34
  #endif

  // NOTE: All pinouts pins must be on the same port
  #define PINOUT_DDR       DDRK
  #define PINOUT_PIN       PINK
  #define PINOUT_PORT      PORTK
  #define PIN_RESET        0  // MEGA2560 Analog Pin 8
  #define PIN_FEED_HOLD    1  // MEGA2560 Analog Pin 9
  #define PIN_CYCLE_START  2  // MEGA2560 Analog Pin 10
  #define PINOUT_INT       PCIE2  // Pin change interrupt enable pin
  #define PINOUT_INT_vect  PCINT2_vect
  #define PINOUT_PCMSK     PCMSK2 // Pin change interrupt register
  #define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))

#endif

#ifdef PIN_MAP_ARDUINO_MEGA_2560_4

#ifndef AXIS_T_TYPE
    #error "The macro "AXIS_T_TYPE" is not defined in 'config.h' !"
#endif

  // Serial port pins
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect

  // NOTE: All step bit and direction pins must be on the same port.
  #define STEPPING_DDR      DDRA
  #define STEPPING_PORT     PORTA
  #define STEPPING_PIN      PINA
  #define X_STEP_BIT        2 // MEGA2560 Digital Pin 24
  #define Y_STEP_BIT        3 // MEGA2560 Digital Pin 25
  #define Z_STEP_BIT        4 // MEGA2560 Digital Pin 26
/// 8c2
  #define T_STEP_BIT        1 // MEGA2560 Digital Pin 23

  #define X_DIRECTION_BIT   5 // MEGA2560 Digital Pin 27
  #define Y_DIRECTION_BIT   6 // MEGA2560 Digital Pin 28
  #define Z_DIRECTION_BIT   7 // MEGA2560 Digital Pin 29
/// 8c2
  #define T_DIRECTION_BIT   0 // MEGA2560 Digital Pin 22
  // All step bits
  #define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<T_STEP_BIT) )
  // All direction bits
  #define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT) |(1<<T_DIRECTION_BIT))

/// <--
  // All stepping-related bits (step/direction)
  #define STEPPING_MASK (STEP_MASK | DIRECTION_MASK)

/// 8c2
   // Define stepper driver enable/disable output pin.
	  #define STEPPERS_DISABLE_DDR    DDRB
	  #define STEPPERS_DISABLE_PORT   PORTB
	  #define STEPPERS_DISABLE_BIT    7  // MEGA2560 Digital Pin 13
	  // STEPPERS_DISABLE_INVERT: Set to 0 for active high stepper disable or 1
	  // for active low stepper disable.
	  #define STEPPERS_DISABLE_INVERT 0
	  #define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)
/// <---
  // NOTE: All limit bit pins must be on the same port
  #define LIMIT_DDR       DDRB
  #define LIMIT_PORT      PORTB
  #define LIMIT_PIN       PINB
  #define X_LIMIT_BIT     4 // MEGA2560 Digital Pin 10
  #define Y_LIMIT_BIT     5 // MEGA2560 Digital Pin 11
  #define Z_LIMIT_BIT     6 // MEGA2560 Digital Pin 12
/// 8c2
	#define T_LIMIT_BIT   3 // MEGA2560 Digital Pin 9

  #define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect  PCINT0_vect
  #define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT) |(1<<T_LIMIT_BIT)) // All limit bits

  #define SPINDLE_ENABLE_DDR   DDRC
  #define SPINDLE_ENABLE_PORT  PORTC
  #define SPINDLE_ENABLE_BIT   2 // MEGA2560 Digital Pin 35

  #define SPINDLE_DIRECTION_DDR   DDRC
  #define SPINDLE_DIRECTION_PORT  PORTC
  #define SPINDLE_DIRECTION_BIT   1 // MEGA2560 Digital Pin 36

  #define COOLANT_FLOOD_DDR   DDRC
  #define COOLANT_FLOOD_PORT  PORTC
  #define COOLANT_FLOOD_BIT   0 // MEGA2560 Digital Pin 37

  // #define ENABLE_M7  // Mist coolant disabled by default. Uncomment to enable.
  #ifdef ENABLE_M7
    #define COOLANT_MIST_DDR   DDRC
    #define COOLANT_MIST_PORT  PORTC
    #define COOLANT_MIST_BIT   3 // MEGA2560 Digital Pin 34
  #endif

  // NOTE: All pinouts pins must be on the same port
  #define PINOUT_DDR       DDRK
  #define PINOUT_PIN       PINK
  #define PINOUT_PORT      PORTK
  #define PIN_RESET        0  // MEGA2560 Analog Pin 8
  #define PIN_FEED_HOLD    1  // MEGA2560 Analog Pin 9
  #define PIN_CYCLE_START  2  // MEGA2560 Analog Pin 10
  #define PROBE			   3  // MEGA2560 Analog Pin 11
  #define PINOUT_INT       PCIE2  // Pin change interrupt enable pin
  #define PINOUT_INT_vect  PCINT2_vect
  #define PINOUT_PCMSK     PCMSK2 // Pin change interrupt register
  #define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))

#endif
/*
#ifdef PIN_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and paste one of the default pin map
  // settings above and modify it to your needs. Then, make sure the defined name is also
  // changed in the config.h file.
#endif
*/

#endif
