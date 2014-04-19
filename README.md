=======================================================================

Grbl_with_Arduino

This directory contains the last versions  April 19, 2014

================================================================================

These are adaptations to build Grbl-xxx in Arduino-xxx (actually xxx=1.0.5 or 1.0.5r2)


A- Grbl83Mega2560  : grbl-0.83 for Mega2560 57600 bauds  4 axis  X, Y, Z, C
                     with M3, M4, M5 and M7, M8, M9 functioning properly active
                     low (configurable in "config.h")
                     
B- Grbl84Mega2560  : grbl-0.84 for Mega2560 57600 bauds  4 axis  X, Y, Z, A
                      axis C -> axis A

C- Grbl8cUno       : grbl-0.8c for Uno328p 115200 bauds  3 axis

D- Grbl9dMega2560  : grbl-0.9d for Mega2560 115200 bauds  3 axis

E- Grbl9dUno       : grbl-0.9d for Uno328p 115200 bauds  3 axis

================================================================================

You simply copy the "GrblxxBoard" directory in "Arduino-xxx/libraries"

Example for Grbl-0.9d for Uno :

1- copy "Grbl9dUno" in "Arduino-105/libraries",

2- load in "Arduino-105" "Examples/Grbl9dUno/Grbl9dUno.ino",

3- compile and upload the Uno card

================================================================================

For any problem use "issues"

================================================================================






