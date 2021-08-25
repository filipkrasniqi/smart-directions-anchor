//
// Created by Filip Krasniqi on 03/11/2020.
//

#ifndef MQTT_PUBLISHER_THREAD_H
#define MQTT_PUBLISHER_THREAD_H

#include <atomic>
#include <thread>
#include "../mosquitto/mosquitto_wrapper.h"
#include "../ble/sniffed_container.h"
#include <mosquitto.h>

class MQTTPublisherThread {
    public:
        void execute();
        void end();
        std::thread start(MQTTPublisher *publisher);
    private:
        std::atomic<bool> terminate{ false };
        MQTTPublisher *publisher;
};

#endif //MQTT_PUBLISHER_THREAD_H