//
// Created by Filip Krasniqi on 03/11/2020.
//

#ifndef BLE_SCANNER_HC_SCANNER_THREAD_H
#define BLE_SCANNER_HC_SCANNER_THREAD_H


#include <atomic>
#include <thread>
#include "utils/mosquitto/mosquitto_wrapper.h"

class HCScannerThread {
    public:
        void execute(MQTTPublisher *publisher);
        void end();
        std::thread start(MQTTPublisher *publisher);
    private:
        std::atomic<bool> terminate{ false };
};


#endif //BLE_SCANNER_HC_SCANNER_THREAD_H
