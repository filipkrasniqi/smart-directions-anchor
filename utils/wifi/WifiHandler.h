//
// Created by Filip Krasniqi on 04/11/2020.
//

#ifndef BLE_SCANNER_WIFIINFO_H
#define BLE_SCANNER_WIFIINFO_H

#include <iostream>
#include <vector>

struct WifiScan {
    std::string mac;
    std::string ssid;
    int rssi;
};

class WifiHandler {
    public:
        std::string getMac();
        std::vector<WifiScan> getScanResults();
        ~WifiHandler();
};

#endif //BLE_SCANNER_WIFIINFO_H