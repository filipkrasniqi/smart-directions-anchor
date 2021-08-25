#include "mqtt_publisher_thread.h"
#include <unistd.h>
#include <string>

void MQTTPublisherThread::execute() {
    this->terminate = false;
    while(!this->terminate) {
        std::string toSend = SniffedContainer::getInstance().pop();
        if(!toSend.empty()) {
            std::cout << "Sending " << toSend << std::endl;
            this->publisher->publish("directions/anchor/proximity", toSend);
        }
        usleep(3000);   // assuming 10Mb/s, 1KB per dequeued, we need .8ms to send it. It should be far enough.
    }
    std::cout << "MQTT scheduler stopped" << std::endl;
}

void MQTTPublisherThread::end() {
    this->terminate = true;
}

/**
* Runs lescan and starts the thread running btmon. 
* Everytime something relevant is found, it is published via MQTT
*/
std::thread MQTTPublisherThread::start(MQTTPublisher *publisher) {
    this->publisher = publisher;
    return std::thread([=] { this->execute(); });
}
