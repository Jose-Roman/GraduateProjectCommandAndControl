//
// Created by Jose Roman  on 12/13/25.
//

#include "CommandAndControl.h"
#include <iostream>

#include "Messaging.h"
#include "CommandExecutor.h"
#include "GenerateScenario.h"
#include "TargetTracker.h"
#include "MissionPlanner.h"
#include "SensorData.h"
#include "Geography.h"

void helloWorld() {
    std::cout << "Hello World from CommandAndControl!" << std::endl;
}

void runCommandAndControl() {

    std::cout << "---- Starting Command and Control System ----" << std::endl;

    // Create shared Messaging helper
    Messaging msg;
    Geography geo;

    // Create system components
    SensorData sensorData(msg);
    TargetTracker targetTracker(msg, geo);
    MissionPlanner missionPlanner(msg, targetTracker);
    CommandExecutor commandExecutor(msg, targetTracker);

    // Initialize subscriptions for messaging system
    commandExecutor.initialize();
    sensorData.initialize();
    targetTracker.initialize();
    missionPlanner.initialize();

    // Kick off the system
    std::cout << "******** ---- [CommandAndControl] Initial Sensor Read ---- ********" << std::endl;
    sensorData.publishSensorData();
    std::cout << "******** ---- [CommandAndControl] Completed ---- ********" << std::endl;
}

void runMission() {
    std::cout << "---- Starting Command and Control Mission System ----" << std::endl;

    // Create shared Messaging helper
    Messaging msg;
    Geography geo;

    // Create system components
    SensorData sensorData(msg);
    TargetTracker targetTracker(msg, geo);
    MissionPlanner missionPlanner(msg, targetTracker);
    CommandExecutor commandExecutor(msg, targetTracker);
    GenerateScenario genScenStart(sensorData, geo, commandExecutor);

    // Initialize subscriptions for messaging system
    commandExecutor.initialize();
    sensorData.initialize();
    targetTracker.initialize();
    missionPlanner.initialize();

    Mission LosAngeles {MissionArea::LosAngeles, "Los Angeles"};
    LosAngeles.targetCounts = {
            {TargetType::Plane, 1},
            {TargetType::Ship, 1},
            {TargetType::Missile, 1}
    };

    LosAngeles.scenarioDuration = 120;

    genScenStart.setFullMission(LosAngeles);
    genScenStart.startScenario();

    std::cout << "******** ---- [CommandAndControl] Mission Completed ---- ********" << std::endl;
}