//
// Created by Filip Krasniqi on 03/11/2020.
//
#include <iostream>


#ifndef BLE_SCANNER_MOSQUITTO_H
#define BLE_SCANNER_MOSQUITTO_H


class MQTTPublisher {
    public:
        explicit MQTTPublisher(std::string, std::string);
        MQTTPublisher(std::string, std::string, int);
        void init(std::string);
        bool connect(std::string, int);
        void publish(std::string, std::string);

    private:
        struct mosquitto *mosq;
        std::string macAddress;
};


#endif //BLE_SCANNER_MOSQUITTO_H
