//
// Created by Filip Krasniqi on 04/11/2020.
//

#include "shell_process.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

/**
Given any shell process, it executes it, returning stout output as a string.
*/
std::string ShellProcess::execute(const char* cmd) {
    FILE* stream = this->startProcess(cmd);
    std::string result = "";
    const int max_buffer = 256;
    char buffer[max_buffer];
    while (!feof(stream)) {
        if (fgets(buffer, max_buffer, stream) != NULL) {
            std::string current_line = buffer;
            result += buffer;
        }
    }
    return result;
}

/**
* Starts the process and returns the associated stream
*/
FILE* ShellProcess::startProcess(const char* cmd) {
    return popen(cmd, "r");
}