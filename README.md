Raspberry-pi FFT
================

The current implementation of this project will read 
a sound stream from pipeline and apply the fft transform
to detect the main frequency of the input sound.

The idea is to use sound commands to control a vehicle
connected to the raspberry-pi.

Dependencies :
------------- 

g++, make

> sudo apt-get install build-essential

Piece of cake instructions : 
-------------

To build : 
> make

To run   : 
> make run

To run other tests, please try : 
> cat samples/sample2.wav | ./exec

> arecord -c 1 | ./exec

