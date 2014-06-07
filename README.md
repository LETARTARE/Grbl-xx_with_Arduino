=======================================================================

Grbl_with_Arduino

This directory contains the last versions  June 7, 2014

================================================================================

These are adaptations to build Grbl-xxx in Arduino-xxx (actually xxx=1.0.5 or 1.0.5r2)

================================================================================

    A-  OFFICIAL VERSIONS 3 AXES    : updated from the site Grbl

1- Grbl8cUno       : grbl-0.8c for Uno328p 115200 bauds  3 axes

2- Grbl8cMega2560  : grbl-0.8c for Mega2560 115200 bauds  3 axes

3- Grbl9dMega2560  : grbl-0.9d for Mega2560 115200 bauds  3 axes

4- Grbl9dUno       : grbl-0.9d for Uno328p 115200 bauds  3 axss

5- Grbl9eMega2560  : grbl-0.9e for Mega2560 115200 bauds  3 axes * update

6- Grbl9eUno       : grbl-0.9e for UNo328p 115200 bauds  3 axes  * update

================================================================================

    B-  UNOFFICIAL VERSIONS 4 AXES     : from the official version 0.8c

1- Grbl8c1Mega2560 : grbl-0.8c1 for Mega2560 57600 bauds  4 axes  X, Y, Z, T
                      
                      with axis T in [A, B, C, U, V, W]

                      mapping Grbl845Mega2560
		       
                      use GrblController-3.6.1-T1 :
                      https://github.com/LETARTARE/GrblHoming/tree/Letartare

2- Grbl8c2Mega2560 : grbl-0.8c2 for Mega2560 57600 bauds  4 axes  X, Y, Z, T * new
                      
                      with axis T in [A, B, C, U, V, W]

                      mapping Grbl8cMega2560 + fourth axis

                      use GrblController-3.6.1-Tx :
                      https://github.com/LETARTARE/GrblHoming/tree/Letartare

================================================================================

    C- UNOFFICIAL VERSION 4 AXES   : from the old version 0.81


1- Grbl845Mega2560 : grbl-0.845 for Mega2560 57600 bauds  4 axes  X, Y, Z, T

                      with axis T in [A, B, C, U, V, W]

                      use GrblController-3.6 :
                      https://github.com/zapmaker/GrblHoming


                      
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






