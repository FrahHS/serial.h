# <img src="https://i.ibb.co/GCf3PBf/pngwing-com-1.png" height="60"> serial.h
Windows c++ library to trade string in serial connection with Arduino (or similar), and your c++ program

## feature

The main.cpp cointain an easy example (commented) to explain how these libraries functions works.

serial.h contains functions to: create connection with your microcontroller, send/receive string to/from Arduino.

## usage

- int sread(int serial, char* buf, int n); read max n byte from connection named 'serial' and place it in buf.

------------


- int swrite(int serial, char* buf, int n); write max n byte to connection named 'serial' from buf.

------------


- int Simple_sopen(char* name, int access, unsigned int speed); easily function to create base serial connection. 
	1. name is the name of serial port(exaple: "COM3").
	1. access is the type of connection(READ or WRITE).
	1. speed is data rate in bits per second (baud) for serial data transmission (for arduino use 9600).

------------


- int SimpleConnect(int access, unsigned int speed); The same of Simple_sopen() but more easy because find in automatic way the serial port.

------------


- simpleserial.cpp contains console functions helps to understand what's going on with cout outputs. (I use that functions in the main.cpp example).

## example

Example_Data_sending.ino contains very few lines to load on arduino for the example program
