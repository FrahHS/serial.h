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

#include <iostream>
#ifndef _SERIAL_
#include "serial.h"
#endif

void retry(int time, int enableLog) {
    if (enableLog) {
        cout << "Serial opening failed, (try to disconnect and reconnect your microcontroller)." << endl;
        cout << "Trying again";
        Sleep(time / 4);
        cout << ".";
        Sleep(time / 4);
        cout << ".";
        Sleep(time / 4);
        cout << ".";
        Sleep(time / 4);
        cout << endl;
    }
    else
        Sleep(2000);
}

int CSimpleConnect(int access, unsigned int speed) { //CSimpleConnect() is the same of SimpleConnect() in serial.h, but with Console log.
    int connection = INCORRECT;
    while (1) {
        AutoSearchSerialPort(access, speed, 'n', 8, 1, &connection);
        if (connection != INCORRECT) {
            cout << "Correctly Connected!" << endl;
            return connection;
        }
        retry(2000, 1);
    }
}
