//
// Created by Filip Krasniqi on 03/11/2020.
//

#ifndef SNIFFED_CONTAINER_H
#define SNIFFED_CONTAINER_H

#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <queue>


typedef struct {
    int rssi;
    std::string timestamp;
    std::string id;
} Sniffed;

class SniffedContainer {

    public:
        // singleton
        static SniffedContainer& getInstance()
        {
            static SniffedContainer instance;   // Guaranteed to be destroyed.
                                                // Instantiated on first use.
            return instance;
        }

        // adds, if not present, a sniffed value to both map and queue
        void add(std::string id, int rssi, std::string timestamp);
        // returns, if present, first added value from queue and removes it from both queue and map
        std::string pop();
    private:
        // singleton
        SniffedContainer() {}
        SniffedContainer(SniffedContainer const&);  // Don't implement
        void operator=(SniffedContainer const&);    // Don't implement
        // map for easier access given id
        std::map<std::string, Sniffed> mapExisting;
        // queue for FIFO sending
        std::queue<Sniffed> queue;
        // lock for add/pop operations
        mutable std::mutex m_mutex;
};

#endif //SNIFFED_CONTAINER_H