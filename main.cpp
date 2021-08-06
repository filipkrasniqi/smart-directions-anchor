#include <iostream>
#include "hc_scanner_thread.h"
#include "utils/wifi/WifiHandler.h"
#include "utils/file/Parser.h"
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
    auto *thread = new HCScannerThread();
    std::thread tw1 = thread->start(publisher);
    int _;
    std::cout << "Type something to end: " << std::endl;
    std::cin >> _;
	thread->end();
    tw1.join();
    return 0;
}
