//
// Created by Filip Krasniqi on 04/11/2020.
//

#ifndef BLE_SCANNER_WIFIINFO_H
#define BLE_SCANNER_WIFIINFO_H

#include <iostream>


class WifiInfo {
    public:
        std::string getMac();
        ~WifiInfo();
};

#endif //BLE_SCANNER_WIFIINFO_H