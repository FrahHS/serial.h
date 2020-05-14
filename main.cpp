#include "serial.h"
#include "simpleserial.cpp"
#include <stdio.h>

using namespace std;

#define SIZE 1024

char Input[SIZE];

int main() {
    int connection = INCORRECT; //instance a serial connection variable.

    connection = CSimpleConnect(READ, 9600); // Arduino connection in reading mode.
    //CSimpleConnect() search the correct COM port and automatically connect at Arduino (C means console, it release console text).
    //SimpleConnect() is the same of CSimpleConnect(), but without Console text.

    //if you need to insert manually the serial port name, you can use Simple_sopen(),
    //ad example to manually insert COM3 port you can:
    //char nport[] = "COM3";
    //wstring name = towstring(nport);
    //connection = Simple_sopen(name, *ACCESS TYPE*, *SPEED*);
    
    int read = 0; // read dimension in byte.

    while (sread(connection, Input, 1) > 0); //buffer cleaning.

    while (1)
    {
        read = sread(connection, Input, 100); //read from connection 100 byte and place all in Input.
        if (read != INCORRECT)
        {
            Input[read] = '\0'; //close Input string.
            cout << Input; //for exemple the program print data received from Arduino.
        }
        if (connection == INCORRECT) { //if the connection isn't working close it and exit.
            sclose(connection);
            return 0;
        }
    }
}
