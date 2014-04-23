=======================================================================

Grbl_with_Arduino

This directory contains the last versions  April 19, 2014

================================================================================

These are adaptations to build Grbl-xxx in Arduino-xxx (actually xxx=1.0.5 or 1.0.5r2)

================================================================================

A- OFFICIAL VERSIONS updated from the site Grbl : 3 axes

A1- Grbl8cUno       : grbl-0.8c for Uno328p 115200 bauds  3 axes

A2- Grbl9dMega2560  : grbl-0.9d for Mega2560 115200 bauds  3 axss

A3- Grbl9dUno       : grbl-0.9d for Uno328p 115200 bauds  3 axss

================================================================================

B- UNOFFICIAL VERSION from the old version 0.81 : 4 axes

B1- Grbl83Mega2560  : grbl-0.83 for Mega2560 57600 bauds  4 axes  X, Y, Z, C
                     with M3, M4, M5 and M7, M8, M9 functioning properly active
                     low (configurable in "config.h")
                     
B2- Grbl84Mega2560  : grbl-0.84 for Mega2560 57600 bauds  4 axes  X, Y, Z, A

================================================================================

You simply copy the "GrblxxBoard" directory in "Arduino-xxx/libraries"

Example for Grbl-0.9d for Uno :

1- copy "Grbl9dUno" in "Arduino-105/libraries",

2- load in "Arduino-105" "Examples/Grbl9dUno/Grbl9dUno.ino",

3- compile and upload the Uno card

************************** VERY IMPORTANT***************************

put ONE VERSION GrblxxBoard in the "libraries" directory

********************************************************************

================================================================================

For any problem use "issues"

================================================================================






