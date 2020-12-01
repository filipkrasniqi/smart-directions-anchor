//
// Created by Filip Krasniqi on 03/11/2020.
//
#include <mosquitto.h>
#include "mosquitto_wrapper.h"
#include <bits/stdc++.h>
#include <assert.h>

/// constructor of a MQTT publisher. 
/// Initializes the mosquitto lib (https://mosquitto.org/api/files/mosquitto-h.html) and connects to a broker.
/// Address is given, macAddress or any string identifier is needed to identify our message.
/// Default port is used, i.e., 1883
MQTTPublisher::MQTTPublisher(std::string address, std::string macAddress) {
    int port = 8884;
    this->macAddress = macAddress;
    this->init(macAddress);
    this->connect(address, port);
}

/// constructor of a MQTT publisher. 
/// Initializes the mosquitto lib (https://mosquitto.org/api/files/mosquitto-h.html) and connects to a broker.
/// Address is given, macAddress or any string identifier is needed to identify our message.
/// Port is given
MQTTPublisher::MQTTPublisher(std::string address, std::string macAddress, int port) {
    this->macAddress = macAddress;
    this->init(macAddress);
    this->connect(address, port);
}

/// In case the mosq struct is not initialized, 
/// it gets initialized
void MQTTPublisher::init(std::string macAddress) {
    if(this->mosq == NULL) {
        mosquitto_lib_init();
        char clientID[macAddress.length()+1];
        strcpy(clientID, macAddress.c_str());
        this->mosq = mosquitto_new(clientID, true, NULL);
        /* 
        TODO I was expecting the need to have what follows:
        int result = mosquitto_tls_set(this->mosq, "/home/pi/keys/mosquitto.org.crt", NULL, "/home/pi/keys/client.crt", "/home/pi/keys/client.key", NULL);
        but it is not working, so the client.cert is not sent.
        */
        int result = mosquitto_tls_set(this->mosq, "/home/pi/keys/mosquitto.org.crt", NULL, NULL, "/home/pi/keys/client.key", NULL);
        if(result == MOSQ_ERR_SUCCESS) {
            std::cout << "MQTT CONNECTION: OK" << std::endl;
        } else if(result == MOSQ_ERR_INVAL) {
            std::cout << "MQTT CONNECTION: seems wrong" << std::endl;
        }
    }
}

/// Connects to address and port as a MQTT publisher
bool MQTTPublisher::connect(std::string address, int port) {
    assert(this->mosq != NULL);
    char message[address.length()+1];
    strcpy(message, address.c_str());
    int rc = mosquitto_connect(this->mosq, message, 1883, 60);  // rc == 0 means connected
    return rc == 0;
}

/// Publishes on a specific target a payload.
/// It attaches before the mac address by default as it is needed in our protocol.
/// Messages will always be MAC$PAYLOAD
/// Currently we assume payload won't include $
void MQTTPublisher::publish(std::string target, std::string payload) {
    payload = this->macAddress + "$" + payload;
    char message[payload.length()+1];
    strcpy(message, payload.c_str());
    mosquitto_publish(mosq, NULL, target.c_str(), payload.length(), message, 0, false);
}
