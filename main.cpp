/*
MIT License
Copyright (c) 2020 FrahHS
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "serial.h"
#include "simpleserial.cpp"

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
