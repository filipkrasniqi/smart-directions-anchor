//
// Created by Filip Krasniqi on 03/11/2020.
//
#include <mosquitto.h>
#include "mosquitto_wrapper.h"
#include <bits/stdc++.h>
#include <assert.h>

#define MQTT_USERNAME "anchor"
#define MQTT_PSW "anchor"

/// constructor of a MQTT publisher. 
/// Initializes the mosquitto lib (https://mosquitto.org/api/files/mosquitto-h.html) and connects to a broker.
/// Address is given, macAddress or any string identifier is needed to identify our message.
/// Default port is used, i.e., 1883
MQTTPublisher::MQTTPublisher(std::string address, std::string macAddress, int nodeID) {
    this->nodeID = nodeID;
    this->macAddress = macAddress;
    int port = 1884;
    this->isMacID = false;
    this->init();
    this->connect(address, port);
}

/// constructor of a MQTT publisher. 
/// Initializes the mosquitto lib (https://mosquitto.org/api/files/mosquitto-h.html) and connects to a broker.
/// Address is given, macAddress or any string identifier is needed to identify our message.
/// Port is given
MQTTPublisher::MQTTPublisher(std::string address, std::string macAddress, int nodeID, int port) {
    this->nodeID = nodeID;
    this->macAddress = macAddress;
    this->isMacID = false;
    this->init();
    this->connect(address, port);
}

std::string MQTTPublisher::getClientID() {
    if(this->isMacID) {
        return this->macAddress;
    } else {
        return std::to_string(this->nodeID);
    }
}

/// In case the mosq struct is not initialized, 
/// it gets initialized
void MQTTPublisher::init() {
    if(this->mosq == NULL) {
        mosquitto_lib_init();
        char clientID[this->getClientID().length()+1];
        strcpy(clientID, this->getClientID().c_str());
        this->mosq = mosquitto_new(clientID, true, NULL);
        int resultAuth = mosquitto_username_pw_set(this->mosq, MQTT_USERNAME, MQTT_PSW);
        if(resultAuth == MOSQ_ERR_SUCCESS) {
            std::cout << "MQTT CONNECTION: OK" << std::endl;
        } else {
            std::cout << "MQTT CONNECTION: seems wrong" << std::endl;
        }
    }
}

/// Connects to address and port as a MQTT publisher
bool MQTTPublisher::connect(std::string address, int port) {
    assert(this->mosq != NULL);
    char message[address.length()+1];
    strcpy(message, address.c_str());
    int rc = mosquitto_connect(this->mosq, message, port, 60);  // rc == 0 means connected
    return rc == 0;
}

/// Publishes on a specific target a payload.
/// The clientID (i.e., MAC) is by default postponed to the target.
void MQTTPublisher::publish(std::string target, std::string payload) {
    this->publish(target, payload, true);
}

/// Publishes on a specific target a payload.
/// The clientID (i.e., MAC or nodeID, depending on isMacID) may or may not be postponed to the target.
void MQTTPublisher::publish(std::string target, std::string payload, bool postponeClientID) {
    if(postponeClientID) {
        target += "/"+this->getClientID();
    }
    char message[payload.length()+1];
    strcpy(message, payload.c_str());
    mosquitto_publish(mosq, NULL, target.c_str(), payload.length(), message, 0, false);
}
