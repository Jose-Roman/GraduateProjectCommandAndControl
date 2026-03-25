//
// Created by Jose Roman  on 12/22/25.
//

#include "MissionPlanner.h"
#include "TargetTracker.h"
#include <iostream>

/**
 * Constructs a MissionPlanner instance.
 *
 * The MissionPlanner is responsible for generating mission-level decisions
 * based on incoming target data. It consumes target updates and produces
 * command messages that are executed downstream by the CommandExecutor.
 */
MissionPlanner::MissionPlanner(Messaging &messaging, TargetTracker &tracker)
            : messaging_(messaging), tracker_(tracker) {}

/**
 * Initializes the MissionPlanner and subscribes to target updates.
 *
 * This enables reactive, event-driven mission planning.
 */
void MissionPlanner::initialize() {
    messaging_.subscribe("target.update",
                            [this](const Message& msg) {
                                onTargetReceived(msg);
                        });
}

/**
 * Sets the current mission configuration.
 *
 * Stores mission parameters - area, target types, and counts.
 * Immediately generates initial targets based on the mission definition
 * and creates corresponding mission plans for each.
 */
void MissionPlanner::setMission(const Mission &mission) {
    currentMission_ = mission;
    std::cout << "[MissionPlanner] Mission set to: "
                << currentMission_.name << std::endl;

    // Generate requested targets
    for (const auto& [type, count] : mission.targetCounts) {
        for (int i = 0; i < count; ++i) {
            Target target = tracker_.trackTarget(currentMission_.area, type);
            planMission(target);
        }
    }
}

/**
 * Callback handler for incoming target update messages.
 *
 * Triggered when a "target.update" message is received. The function
 * deserializes the target data from the message payload and invokes
 * mission planning logic for that target.
 */
void MissionPlanner::onTargetReceived(const Message& msg) {
    std::cout << "[MissionPlanner] Target update received: "
                << msg.payload << std::endl;

    // For this initial prototype, simulate extracting target data
    Target target = tracker_.deserializeTarget(msg.payload);

    planMission(target);
}

/**
 * @brief Generates and publishes a mission plan for a given target.
 *
 * This function simulates decision-making logic by analyzing the target's
 * position, altitude, and speed. It increments the target update count,
 * logs relevant information, and creates a command message for execution.
 *
 * The generated command is serialized and published to the
 * "command.execute" topic for the CommandExecutor to process.
 */
void MissionPlanner::planMission(Target &track) {
    track.numOfUpdates = ++track.numOfUpdates;
    std::cout << "[MissionPlanner] Planning Mission for Target: "
                << track.id << " at ("
                << track.latitude << ", "
                << track.longitude << ")"
                << std::endl;

    std::cout << "[MissionPlanner] Target Altitude: " << track.altitude<< std::endl;
    std::cout << "[MissionPlanner] Target Speed: " << track.speed << std::endl;


    //std::cout << "[MissionPlanner] Num of Updates: " << track.numOfUpdates << std::endl;

    // Create a command message for the CommandExecutor
    Message commandMsg;
    commandMsg.topic = "command.execute";
    commandMsg.payload = tracker_.serializeTarget(track);
    commandMsg.source = "MissionPlanner";

    messaging_.publish(commandMsg);
}

/**
 * Generates a mission plan based on mission area context.
 *
 * This function simulates different mission descriptions based on area.
 */
void MissionPlanner::planMissionArea(Target &target) {
    target.numOfUpdates = ++target.numOfUpdates;

    std::cout << "[MissionPlanner] Planning Mission Area: "
                << currentMission_.name << std::endl;

    switch (currentMission_.area) {
        case MissionArea::LosAngeles:
            std::cout << "[MissionPlanner] Los Angeles: Coastal air & maritme monitoring" << std::endl;
            break;
        case MissionArea::NewYork:
            std::cout << "[MissionPlanner] New York: Dense urban airspace coordination" << std::endl;
            break;
        case MissionArea::Miami:
            std::cout << "[MissionPlanner] Miami: Dense urban airspace coordination" << std::endl;
            break;
    }
}
