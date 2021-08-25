#include <iostream>
#include "ble_sniffer_thread.h"
#include "utils/wifi/WifiHandler.h"
#include "utils/file/Parser.h"
#include "utils/scheduler/mqtt_publisher_thread.h"
#include <thread>
#include <fstream>

#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
//#include <HTTPRequest.h>

int main() {
    std::string address = "80.211.69.17";
    Parser *parser = new Parser();
    WifiHandler *wifi = new WifiHandler();

    if(parser->getSDInstanceID() < 0 || parser->getNodeID() < 0) {
        std::cout << "ERROR: need init of node and SD instance" << std::endl;
        exit(0);
    }

    std::string macAddress = wifi->getMac();

    MQTTPublisher *publisher = new MQTTPublisher(address, macAddress, parser->getNodeID());
    std::cout << "Publisher initialized " << std::endl;
    auto *thread = new BLESnifferThread();
    std::thread tw1 = thread->start();
    auto *thread2 = new MQTTPublisherThread();
    std::thread tw2 = thread2->start(publisher);
    int _;
    while(true) {
        //std::cout << "Type something to end: " << std::endl;
        //std::cin >> _;
        usleep(60000000);
    }
	//thread->end();
	//thread2->end();
    //tw1.join();
    //tw2.join();
    return 0;
}
