//
// Created by Filip Krasniqi on 04/11/2020.
//

#ifndef BLE_SCANNER_WIFIINFO_H
#define BLE_SCANNER_WIFIINFO_H

#include <iostream>
#include <vector>

// TODO mettere qui una struct
// TODO dopodiche usare questo handler eseguendo il processo

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