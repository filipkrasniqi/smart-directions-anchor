#include <iostream>
#include "hc_scanner_thread.h"
#include "utils/wifi/WifiInfo.h"
#include <thread>

int main() {
    std::string address = "192.168.1.151";
    WifiInfo *wifi = new WifiInfo();
	
    std::string macAddress = wifi->getMac();

    MQTTPublisher *publisher = new MQTTPublisher(address, macAddress);
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
