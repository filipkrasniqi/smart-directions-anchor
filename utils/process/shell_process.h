//
// Created by Filip Krasniqi on 04/11/2020.
//

#ifndef BLE_SCANNER_PROCESS_H
#define BLE_SCANNER_PROCESS_H

#include <iostream>

class ShellProcess {
    public:
        std::string execute(const char*);
        ~ShellProcess();
};


#endif //BLE_SCANNER_PROCESS_H
