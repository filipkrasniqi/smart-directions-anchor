//
// Created by Filip Krasniqi on 04/11/2020.
//

#include "Parser.h"
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

Parser::Parser() {
	this->nodeID = -1;
	this->sdInstanceID = -1;
}

/**
* Reads from file NodeID if present. If not, returns -1
*/
int Parser::getNodeID() {
	if(this->nodeID < 0) {
		this->nodeInfoHandler = std::ifstream("/home/pi/ble_scanner/assets/node.info");
		
		if(this->nodeInfoHandler.good()) {
			std::string text;
			std::getline(this->nodeInfoHandler, text);
			try {
				this->nodeID = std::stoi(text);
			} catch(std::exception e) {
				// no value: not good, taking default value = -1
				this->nodeID = -1;
			}
		} else {
			this->nodeID = -1;
		}
	}
	return this->nodeID;
}

/**
* Reads from file SmartDirectionInstanceID if present. If not, returns -1
*/
int Parser::getSDInstanceID() {
	if(this->sdInstanceID < 0) {
		this->nodeSetupHandler = std::ifstream("/home/pi/ble_scanner/assets/node.setup");

		if(this->nodeSetupHandler.good()) {
			std::string text;
			std::getline(this->nodeSetupHandler, text);
			try {
				this->sdInstanceID = std::stoi(text);
			} catch(std::exception e) {
				// no value: not good, taking default value = -1
				this->sdInstanceID = -1;
			}
		} else {
			this->sdInstanceID = -1;
		}
	}
	return this->sdInstanceID;
}