//
// Created by Filip Krasniqi on 04/11/2020.
//

#include "WifiHandler.h"
#include <iostream>
#include "../process/shell_process.h"
#include <sys/socket.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>
#include <vector>

/**
 * Executes shell command to get mac address of wlan
 * */
std::string WifiHandler::getMac() {
	ShellProcess *process = new ShellProcess();
	// trying with wlan
	std::string mac = process->execute("cat /sys/class/net/wlan0/address");
	if(mac.length() <= 0) {
		// trying with eth
		mac = process->execute("cat /sys/class/net/eth0/address");
		if(mac.length() <= 0) {
			// none is working, shutting down
			std::cerr << "No interface available to identify the unit" << std::endl;
			throw;
		}
	}
	mac = mac.substr(0, mac.length() - 1);
	return mac;
}

static std::string trim(std::string s, std::string valToTrim) {
	int pos = s.find(valToTrim);
	while (pos != std::string::npos && pos <= 0) {
		s.erase(0, 1);
		pos = s.find(valToTrim);
	}
	return s;
}

/**
* Uses iw to scan for nearby APs.
*/
std::vector<WifiScan> WifiHandler::getScanResults() {
	ShellProcess *process = new ShellProcess();
	std::string scanResults = process->execute("iw dev wlan0 scan");
	std::vector<WifiScan> results;

	size_t pos = 0;
	std::string currentAP;
	std::string tokenAP = "BSS";
	std::string lineDelimiter = "\n";
	std::string macDelimiter = "(";
	std::string valueDelimiter = ": ";
	std::string spaceDelimiter = " ";
	std::string tabDelimiter = "\t";

	// iterate line by line
	int i = 0;
	while ((pos = scanResults.find(tokenAP)) != std::string::npos) {
		currentAP = scanResults.substr(0, pos);
		scanResults.erase(0, pos + tokenAP.length());
		std::string firstLine = currentAP.substr(0, currentAP.find(lineDelimiter));
		int positionInLine = firstLine.find("on wlan0");
		if(positionInLine != std::string::npos) {
			// it means we are in the correct block
			std::string macAddress = firstLine.substr(1, 17);
			
			size_t rowPos = 0;
			int rssi = 1;
			std::string SSID = "";
			while ((rowPos = currentAP.find(lineDelimiter)) != std::string::npos) {
				std::string currentRow = currentAP.substr(0, rowPos);
				int positionInLine = currentRow.find(valueDelimiter);
				std::string fieldName = currentRow.substr(0, positionInLine);
				
				// trim initial spaces or tabs
				fieldName = trim(fieldName, spaceDelimiter);
				fieldName = trim(fieldName, tabDelimiter);
				
				currentRow.erase(0, positionInLine + valueDelimiter.length());
				if(std::string("signal").compare(fieldName) == 0) {
					std::string rssiToken = " dBm";
					int posRSSI = currentRow.find(rssiToken);
					std::string value = currentRow.substr(0, posRSSI);
					currentRow.erase(0, posRSSI + rssiToken.length());
					rssi = std::stoi(value);
				}
				if(std::string("SSID").compare(fieldName) == 0) {
					// TODO check se ...
					SSID = currentRow;
				}
				if(rssi < 0 && SSID.compare("") != 0) {
					results.push_back({macAddress, SSID, rssi});
				}
				currentAP.erase(0, rowPos + lineDelimiter.length());
			}
		}
	}

	return results;
}