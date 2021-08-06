//
// Created by Filip Krasniqi on 03/11/2020.
//
#include <iostream>


#ifndef BLE_SCANNER_MOSQUITTO_H
#define BLE_SCANNER_MOSQUITTO_H


class MQTTPublisher {
    public:
        explicit MQTTPublisher(std::string, std::string, int);
        MQTTPublisher(std::string, std::string, int, int);
        void init();
        bool connect(std::string, int);
        void publish(std::string, std::string);
        void publish(std::string, std::string, bool postponeClientID);
        std::string getClientID();

    private:
        struct mosquitto *mosq;
        std::string macAddress;
        int nodeID;
        bool isMacID;
};


#endif //BLE_SCANNER_MOSQUITTO_H
