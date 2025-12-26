//
// Created by Jose Roman  on 12/22/25.
//

#include "CommandExecutor.h"
#include <iostream>

// Command Executor constructor
CommandExecutor::CommandExecutor(Messaging &messaging) : messaging_(messaging) {}

// Registers the CommandExecutor as a subscriber and sets up the communication link between
// the messaging system and the command execution logic
void CommandExecutor::initialize() {
    messaging_.subscribe("command.execute",
        [this](const Message& msg) {
            onCommandReceived((msg));
        });
}

// Handles incoming command execution messages received from the messaging system.
// Simulates execution and publishes a status
void CommandExecutor::onCommandReceived(const Message &msg) const {
    std::cout << "[CommandExecutor] Command Received: "
                << msg.payload << std::endl;
    //Simulated execution
    std::cout << "[CommandExecutor] Executing command ..." << std::endl;

    Message statusMsg;
    statusMsg.topic = "command.status";
    statusMsg.payload = "Command executed successfully";
    statusMsg.timestamp = msg.timestamp;
    statusMsg.source = "CommandExecutor";

    messaging_.publish(statusMsg);
}

// Simulates a command execution without messaging
void CommandExecutor::executeCommand(const std::string &command) {
    std::cout << "[CommandExecutor] Executing Command: " << command << std::endl;
}
