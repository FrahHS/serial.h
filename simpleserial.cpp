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