#include "sniffed_container.h"
#include <cstdio>
#include <iostream>

void SniffedContainer::add(std::string id, int rssi, std::string timestamp) {
    // atomic function
    std::lock_guard<std::mutex> lock(m_mutex);
    // check if exists: only if not, I add it
    std::map<std::string,Sniffed>::iterator it = mapExisting.find(id);
    if(it == mapExisting.end()) {
        //std::cout << "Enqueuing" << std::endl;
        Sniffed s = {rssi, timestamp, id};
        mapExisting[id] = s;
        queue.push(s);
    } else {
        //std::cout << "Attempted Enqueuing" << std::endl;
    }
}

std::string SniffedContainer::pop() {
    // atomic function
    std::lock_guard<std::mutex> lock(m_mutex);
    // checks if anything is present
    // if so, returns last added value: obj is given from queue, then map is also emptied
    //std::cout << "Attempt dequeueing..." << std::endl;
    if(queue.empty()) {
        return "";
    } else {
        //std::cout << "Dequeuing" << std::endl;
        Sniffed toReturn = queue.front();
        std::string msg_string = (toReturn.id + "$" + std::to_string(toReturn.rssi) + "$" + toReturn.timestamp);
        queue.pop();
        mapExisting.erase(toReturn.id);
        
        return msg_string;
    }
}