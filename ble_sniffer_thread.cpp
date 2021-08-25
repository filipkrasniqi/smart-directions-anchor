//
// Created by Filip Krasniqi on 03/11/2020.
//

#include <iostream>
#include "ble_sniffer_thread.h"
#include <thread>
#include <atomic>
#include <sstream>
#include <cstdio>
#include <vector>
#include <mosquitto.h>
#include <bits/stdc++.h>
#include <unistd.h>

void BLESnifferThread::execute() {
    this->terminate = false;
    while(!this->terminate) {
        /// executing process in s.w.t. I take its stdout; won't work with ShellProcess class
        const char *cmd = "btmon";
        FILE* stream = popen(cmd, "r");
        std::string currentUUID = "";
        std::string rssi = "";
        char delim = ' ';
        const int max_buffer = 256;
        char buffer[max_buffer];
        while (!feof(stream) && !this->terminate) {
            if (fgets(buffer, max_buffer, stream) != NULL) {
                // data.append(buffer);
                std::string current_line = buffer;

                /// defining whether I am in a useless row, taking UUID or RSSI
                std::size_t found_UUID = current_line.find("Data: beac");
                std::size_t found_rssi = current_line.find("RSSI");
                /// this instead tells whether previous group was useless
                std::size_t found_start_group = current_line.find("HCI Event");

                if(found_start_group!=std::string::npos) {
                    // start from beginning
                    rssi = "";
                    currentUUID = "";
                }

                if (found_UUID!=std::string::npos || found_rssi!=std::string::npos) {
                    /// something good.
                    /// Text has some spaces at first, then it contains Data: beac<UUID> or RSSI: <val> <junk>
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

                    i = 0;

                    if(found_UUID!=std::string::npos) {
                        // it means we are in the correct block for UUID
                        currentUUID = sanitizedString.substr(10, 32);
                        // as we expect before to find rssi, we reset it to avoid communication of previous RSSIs associated to our beacon
                        rssi = "";
                    }

                    if(found_rssi != std::string::npos) {
                        std::size_t pos_dbm = sanitizedString.find(" dBm");
                        if(pos_dbm == std::string::npos) {
                            //std::cout << "Something wrong here..." << std::endl;
                        } else {
				            rssi = sanitizedString.substr(6, pos_dbm-6);
                        }

                    }
                }
            }
		
            /// whenever I have both values it means I parsed data for one device. I enqueue them.
            if(!rssi.empty() && !currentUUID.empty()) {
                std::string currentTimestamp = std::to_string(std::time(0));
                SniffedContainer::getInstance().add(currentUUID, std::stoi(rssi), currentTimestamp);
                rssi = "";
                currentUUID = "";
            }
        }
        std::cout << "Finished stream!!!" << std::endl;
    }
    std::cout << "Scanner thread stopped" << std::endl;
}

void BLESnifferThread::end() {
    this->terminate = true;
}

/**
* Runs lescan and starts the thread running btmon. 
* Everytime something relevant is found, it is published via MQTT
*/
std::thread BLESnifferThread::start() {
    return std::thread([=] { this->execute(); });
}
