//
// Created by Filip Krasniqi on 03/11/2020.
//

#include <iostream>
#include "hc_scanner_thread.h"
#include <thread>
#include <atomic>
#include <sstream>
#include <cstdio>
#include <vector>
#include <mosquitto.h>
#include <bits/stdc++.h>
#include <unistd.h>

void HCScannerThread::execute(MQTTPublisher *publisher) {
    this->terminate = false;
    while(!this->terminate) {
        /// executing process in s.w.t. I take its stdout
        const char *cmd = "sudo hcitool lescan --duplicates | sudo hcidump";
        FILE* stream = popen(cmd, "r");
        std::string currentMAC = "";
        std::string rssi = "";
        char delim = ' ';
        const int max_buffer = 256;
        char buffer[max_buffer];
        while (!feof(stream) && !this->terminate) {
            if (fgets(buffer, max_buffer, stream) != NULL) {
                // data.append(buffer);
                std::string current_line = buffer;

                /// defining whether I am in a useless row, taking MAC or RSSI
                std::size_t found_bdaddr = current_line.find("bdaddr");
                std::size_t found_rssi = current_line.find("RSSI");

                if (found_bdaddr!=std::string::npos || found_rssi!=std::string::npos) {
                    /// something good.
                    /// Text has some spaces at first, then it contains a string s.t. splitted with ' ' gives the value at [1]
                    std::string sanitizedString = "";
                    int i = 0;
                    bool hasEncounteredChar = false;
                    /// sanitizing string by trimming first part
                    while(i < current_line.length()) {
                        hasEncounteredChar = hasEncounteredChar || (current_line[i] != ' ');
                        if(hasEncounteredChar) {
                            sanitizedString += current_line.at(i);
                        }
                        i++;
                    }

                    std::istringstream currentRowStream(sanitizedString);
                    std::string currentInstance;
                    i = 0;
                    /// retrieving splitted string. In both cases we have value = split[1]
                    while (std::getline(currentRowStream, currentInstance, delim)) {
                        if(i == 1) {
                            if(found_bdaddr!=std::string::npos) {
                                currentMAC = currentInstance;
                            } else {
                                rssi = currentInstance.substr(0, currentInstance.length() - 1);
                            }
                        }
                        i++;
                    }
                }
            }
            /// whenever I have both values it means I parsed data for one device. I send them to the broker.
            if(rssi != "" && currentMAC != "") {
                std::string msg_string = (currentMAC + "$" + rssi);
                publisher->publish("ble/rssi", msg_string);
                rssi = "";
                currentMAC = "";
            }
            // usleep(20000);
        }
        std::cout << "Finished stream!!!" << std::endl;
        usleep(50000);
    }
    std::cout << "Scanner thread stopped" << std::endl;
}

void HCScannerThread::end() {
    this->terminate = true;
}

std::thread HCScannerThread::start(MQTTPublisher *publisher) {
    return std::thread([=] { this->execute(publisher); });
}