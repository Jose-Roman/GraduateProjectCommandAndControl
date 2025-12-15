//
// Created by Jose Roman  on 12/14/25.
//

#ifndef GRADUATEPROJECT_COMMANDCORE_H
#define GRADUATEPROJECT_COMMANDCORE_H

#pragma once
#include <string>

namespace command {
    struct Result {
        int code;
        std::string message;
    };


    Result send_command(const std::string& cmd,
                        const std::string& payload);

    void initialize();
    void shutdown();
}

#endif //GRADUATEPROJECT_COMMANDCORE_H