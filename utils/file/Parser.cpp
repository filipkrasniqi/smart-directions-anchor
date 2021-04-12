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

int Parser::getNodeID() {
	if(this->nodeID < 0) {
		this->nodeInfoHandler = std::ifstream("../assets/node.info");
		// check if file is good
		if(this->nodeInfoHandler.good()) {
			std::string text;
			std::getline(this->nodeInfoHandler, text);
			try {
				this->nodeID = std::stoi(text);
			} catch(std::exception e) {
				// no value
			}
		} else {
			this->nodeID = -1;
		}
	}
	return this->nodeID;
}
int Parser::getSDInstanceID() {
	if(this->sdInstanceID < 0) {
		this->nodeSetupHandler = std::ifstream("../assets/node.setup");

		if(this->nodeSetupHandler.good()) {
			std::string text;
			std::getline(this->nodeSetupHandler, text);
			try {
				this->sdInstanceID = std::stoi(text);
			} catch(std::exception e) {
				// no value
				std::cout << "STOI EXC" << std::endl;
			}
		} else {
			this->sdInstanceID = -1;
		}
	}
	return this->sdInstanceID;
}