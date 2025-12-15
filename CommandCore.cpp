//
// Created by Jose Roman  on 12/14/25.
//

#include "CommandCore.h"
#include <iostream>

namespace command {
    void initialize() {
        std::cout << "[C++] Command Core Initialized" << std::endl;
    }

    Result send_command(const std::string& cmd,
                        const std::string& payload) {
        if (cmd == "PING") {
            return {0, "PONG"};
        }
        return {1, "UNKNOWN"};
    }

    void shutdown() {
        std::cout << "[C++] Shutdown Command Core" << std::endl;
    }

}