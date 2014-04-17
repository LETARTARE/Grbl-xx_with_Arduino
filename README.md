=======================================================================

Grbl_with_Arduino

This directory "devArduino" contains versions developments or changed

================================================================================

These are adaptations to build Grbl-xxx in Arduino-xxx (actually xxx=1.0.5 or 1.0.5r2)

A- Grbl82Mega2560  : grbl-0.82 for Mega2560 57600 bauds  4 axis
                    grbl-0.82 is an adapted version of grbl-0.81
                    ("https://github.com/LETARTARE/Mega2560-grbl-0.81")

B- Grbl8cUno       : grbl-0.8c for Uno328p 115200 bauds  3 axis

C- Grbl9dMega2560  : grbl-0.9d for Mega2560 115200 bauds  3 axis

D- Grbl9dUno       : grbl-0.9d for Uno328p 115200 bauds  3 axis

================================================================================

You simply copy the "GrblxxBoard" directory in "Arduino-xxx/libraries"

Example for Grbl-0.9d for Uno :

1- copy "Grbl9dUno" in "Arduino-105/libraries",

2- load in "Arduino-105" "Examples/Grbl9dUno/Grbl9dUno.ino",

3- compile and upload the Uno card

================================================================================






