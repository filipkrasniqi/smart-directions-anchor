//
// Created by Filip Krasniqi on 04/11/2020.
//

#include "shell_process.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

std::string ShellProcess::execute(const char* cmd) {
    FILE* stream = popen(cmd, "r");
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

std::string ShellProcess::execCommand(const std::string cmd, int& out_exitStatus)
{
    out_exitStatus = 0;
    auto pPipe = ::popen(cmd.c_str(), "r");
    if(pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 128> buffer;

    std::string result;

    while(not std::feof(pPipe))
    {
        auto bytes = std::fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if(WIFEXITED(rc))
    {
        out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}