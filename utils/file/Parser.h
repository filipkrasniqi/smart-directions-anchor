//
// Created by Filip Krasniqi on 04/11/2020.
//

#ifndef BLE_SCANNER_PARSER_H
#define BLE_SCANNER_PARSER_H

#include <iostream>
#include <fstream>

class Parser {
    public:
        Parser();
        int getNodeID();
        int getSDInstanceID();
        ~Parser();
    private:
        std::ifstream nodeInfoHandler;
        std::ifstream nodeSetupHandler;
        int nodeID;
        int sdInstanceID;
};

#endif //BLE_SCANNER_PARSER_H