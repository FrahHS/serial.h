/* MIT License
 * Copyright (c) 2020 FrahHS
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _SERIAL_
#define _SERIAL_
#include "helper.h"

using namespace std;

//screate create a serial connection using the c++ function CreateFile from Windows Api.
int screate(wstring com, int access, unsigned int speed, char parity, unsigned int bits, unsigned int stop) {
    DCB dcb;
    HANDLE fileHandle; 

    fileHandle = CreateFile(com.c_str(), access, 0, 0, OPEN_EXISTING, 0, 0);
  
    if (fileHandle == INVALID_HANDLE_VALUE)
        return INCORRECT;

    memset(&dcb, sizeof(dcb), 0); 
    dcb.DCBlength = sizeof(dcb); 

    char settings[100];
    sprintf(settings, "%d,%c,%d,%d", speed, parity, bits, stop);
    wstring set = towstring(settings);
    if (!BuildCommDCB(set.c_str(), &dcb))
        return INCORRECT;
   
    if (!SetCommState(fileHandle, &dcb))
        return INCORRECT;

    if (!SetupComm(fileHandle, 1024, 1024))
            return INCORRECT;

    COMMTIMEOUTS to;

    to.ReadIntervalTimeout = 100;
    to.ReadTotalTimeoutMultiplier = 50;
    to.ReadTotalTimeoutConstant = 0;
    to.WriteTotalTimeoutConstant = 1000;
    to.WriteTotalTimeoutMultiplier = 1000;
 
    if (!SetCommTimeouts(fileHandle, &to))
        return INCORRECT;
    return (int)fileHandle;
}


int sread(int serial, char* buf, int n) { //read max n byte from connection named 'serial' and place it in buf.
    DWORD x;
    ReadFile((void*)serial, buf, n, &x, NULL);
    if (x == 0)
        return INCORRECT;
    return x; //return dimension in byte of date read.
}

int swrite(int serial, char* buf, int n) { //write max n byte to connection named 'serial' from buf.
    DWORD x;
    WriteFile((void*)serial, buf, n, &x, NULL);
    if (x == 0)
        return INCORRECT;
    return x;
}

int Simple_sopen(char* name, int access, unsigned int speed) { //easily function to create base serial connection.
    wstring wname;
    wname = towstring(name);
    int connection = INCORRECT;
    connection = screate(wname, access, speed, 'n', 8, 1);
    return connection;
}

//automatic arduino serial port finder, for lazy people.
char* AutoSearchSerialPort(int access, unsigned int speed, char parity, unsigned int bits, unsigned int stop, int * pointerconnection) {
    int connection = INCORRECT;
    int read = 0;
    wstring name;
    char nport[7] = "COM0";
    nport[5] = '\0'; //inizialize all the not inizialized char of the array at '\0'.
    nport[6] = '\0';
    for (int c = 0; c < 10; c++) {    //Check the strings from the "COM0" to the "COM999".
        for (int d = 0; d < 10; d++) {    
            for (int n = 0; n < 10; n++) {
                if (c == 0) {
                    if (d == 0)
                        nport[3] = '0' + n;
                    else {
                        nport[3] = '0' + d;
                        nport[4] = '0' + n;
                    }
                }
                else {
                    nport[3] = '0' + c;
                    nport[4] = '0' + d;
                    nport[5] = '0' + n;
                }

                name = towstring(nport);

                connection = screate(name, access, speed, parity, bits, stop);
                if (connection != INCORRECT) {
                    *pointerconnection = connection; //pass the connection to pointerconnection.
                    return nport; //return char pointer of name of serial port.
                }
            }
        }
    }
 
    return NULL;
}

int SimpleConnect(int access, unsigned int speed) { //the same of Simple_sopen() but more easy because find in automatic way the serial port.
    int connection = INCORRECT;
    while (1) {
        AutoSearchSerialPort(access, speed, 'n', 8, 1, &connection);
        if (connection != INCORRECT) {
            return connection;
        }
        Sleep(500);
    }
}

void sclose(int serial) { //close the serial connection.
    CloseHandle((void*)serial);
}
#endif //_SERIAL_
