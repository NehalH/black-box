## Black-Box
A device that records flight data (pitch) per unit time, hence the name 'Black-Box'

Here is how the Black Box works:

The device contains 5 major components:
1. A microcontroller.
2. Electronic Gyroscope & accelerometer.
3. SD Card module.
4. SD card.
5. 9V battery.

The Electronic Gyroscope and accelerometer reads the Angular velocity and acceleration in real-time. 

This data is then sent to the microcontroller where it is processed using certain mathematical functions.

This processed data is further stored into the SD card along with the Time stamp.

The firmware of the microcontroller is written using embedded C language.

The end result is a set of data in Log format, where the current time and the current angles in the X,Y, and Z axes are stored.

The microcontroller only requires a small sized battery as it requires only a 5V input voltage. This makes the setup light and compact. 

The entire device weighs less than 120 grams.
