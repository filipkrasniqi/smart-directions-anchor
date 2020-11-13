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
    int port = 1883;
    this->macAddress = macAddress;
    this->init();
    this->connect(address, port);
}

/// constructor of a MQTT publisher. 
/// Initializes the mosquitto lib (https://mosquitto.org/api/files/mosquitto-h.html) and connects to a broker.
/// Address is given, macAddress or any string identifier is needed to identify our message.
/// Port is given
MQTTPublisher::MQTTPublisher(std::string address, std::string macAddress, int port) {
    this->macAddress = macAddress;
    this->init();
    this->connect(address, port);
}

/// In case the mosq struct is not initialized, 
/// it gets initialized
void MQTTPublisher::init() {
    if(this->mosq == NULL) {
        mosquitto_lib_init();
        this->mosq = mosquitto_new("publisher-test", true, NULL);
	int result = mosquitto_username_pw_set(this->mosq, "test", "password123");
	std::cout << "PSW RESULT: " << result << std::endl;
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
