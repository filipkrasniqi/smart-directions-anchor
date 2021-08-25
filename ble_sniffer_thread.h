//
// Created by Filip Krasniqi on 03/11/2020.
//

#ifndef BLE_SCANNER_HC_SCANNER_THREAD_H
#define BLE_SCANNER_HC_SCANNER_THREAD_H


#include <atomic>
#include <thread>
#include "utils/mosquitto/mosquitto_wrapper.h"
#include "utils/scheduler/scheduler.h"
#include "utils/ble/sniffed_container.h"
#include <mosquitto.h>

class BLESnifferThread {
    public:
        void execute();
        void end();
        std::thread start();
    private:
        std::atomic<bool> terminate{ false };
};


#endif //BLE_SCANNER_HC_SCANNER_THREAD_H
