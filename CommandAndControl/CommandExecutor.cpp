//
// Created by Jose Roman  on 12/22/25.
//

#include "CommandExecutor.h"
#include <iostream>

/**
 * Command Executor constructor
 *
 * The CommandExecutor is responsible for receiving mission commands and
 * executing them. It acts as the final stage in the command-and-control
 * pipeline, consuming messages from the MissionPlanner and triggering
 * target updates through the TargetTracker.
 */
CommandExecutor::CommandExecutor(Messaging &messaging, TargetTracker &tracker)
: messaging_(messaging), tracker_(tracker) {}


/**
 * Registers the CommandExecutor as a subscriber and sets up the communication link
 * between the messaging system and the command execution logic
 */
void CommandExecutor::initialize() {
    std::cout << "[CommandExecutor] Command Executor initialized" << std::endl;

    messaging_.subscribe("command.execute",
        [this](const Message& msg) {
            onCommandReceived((msg));
        });
}

/**
 * Handles incoming command execution messages.
 *
 * It simulates command execution, logs the activity, and publishes a status
 * update indicating successful execution.
 */
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

    Target track = tracker_.deserializeTarget(msg.payload);

    // update track
    tracker_.updateTrack(track.id, missionDuration_);
}

/**
 * Simulates a command execution without messaging
 *
 * Useful for testing or standalone execution scenarios.
 */
void CommandExecutor::executeCommand(const std::string &command) {
    std::cout << "[CommandExecutor] Executing Command: " << command << std::endl;
}

/**
 * Sets the duration of the mission scenario.
 *
 * The scenario duration determines how long target updates will be simulated
 * during command execution.
 */
void CommandExecutor::setScenarioDuration(int scenarioDuration) {
    missionDuration_ = scenarioDuration;
}
