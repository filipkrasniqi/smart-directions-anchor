//
// Created by Filip Krasniqi on 04/11/2020.
//

#include "WifiInfo.h"
#include <iostream>
#include "../process/shell_process.h"
#include <sys/socket.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>

/**
 * Executes shell command to get mac address of wlan
 * */
std::string WifiInfo::getMac() {
	ShellProcess *process = new ShellProcess();
	// trying with wlan
	std::string mac = process->execute("cat /sys/class/net/wlan0/address");
	if(mac.length() <= 0) {
		// trying with eth
		mac = process->execute("cat /sys/class/net/eth0/address");
		if(mac.length() <= 0) {
			// fuck them all
			std::cerr << "No interface available to identify the unit" << std::endl;
			throw;
		}
	}
	mac = mac.substr(0, mac.length() - 1);
	return mac;
}