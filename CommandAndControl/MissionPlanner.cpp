//
// Created by Jose Roman  on 12/22/25.
//

#include "MissionPlanner.h"
#include <iostream>

// Constructor
MissionPlanner::MissionPlanner(Messaging &messaging, TargetTracker &tracker)
            : messaging_(messaging), tracker_(tracker) {}

// Registers the MissionPlanner to listen for target tracking updates
void MissionPlanner::initialize() {
    messaging_.subscribe("target.update",
                            [this](const Message& msg) {
                                onTargetReceived(msg);
                        });
}

// Handles incoming target tracking messgaes
void MissionPlanner::onTargetReceived(const Message& msg) {
    std::cout << "[MissionPlanner] Target update received: "
                << msg.payload << std::endl;

    // For this initial prototype, simulate extracting target data
    Target target = tracker_.trackTarget();

    planMission(target);
}

// Generates a simple mission plan based on the target
void MissionPlanner::planMission(Target &track) {
    track.numOfUpdates = ++track.numOfUpdates;
    std::cout << "[MissionPlanner] Planning Mission for Target: "
                << track.id << " at ("
                << track.x << ", "
                << track.y << ")"
                << std::endl;
    //std::cout << "[MissionPlanner] Num of Updates: " << track.numOfUpdates << std::endl;

    // Create a command message for the CommandExecutor
    Message commandMsg;
    commandMsg.topic = "command.execute";
    commandMsg.payload = "Engage Target";
    commandMsg.source = "MissionPlanner";

    messaging_.publish(commandMsg);
}
