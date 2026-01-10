//
// Created by Jose Roman  on 12/13/25.
//

#include "CommandAndControl.h"
#include <iostream>

#include "Messaging.h"
#include "CommandExecutor.h"
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
    CommandExecutor commandExecutor(msg);
    SensorData sensorData(msg);
    TargetTracker targetTracker(msg, geo);
    MissionPlanner missionPlanner(msg, targetTracker);

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
    CommandExecutor commandExecutor(msg);
    SensorData sensorData(msg);
    TargetTracker targetTracker(msg, geo);
    MissionPlanner missionPlanner(msg, targetTracker);

    // Initialize subscriptions for messaging system
    commandExecutor.initialize();
    sensorData.initialize();
    targetTracker.initialize();
    missionPlanner.initialize();

    Mission LosAngeles {MissionArea::LosAngeles, "Los Angeles"};
    LosAngeles.targetCounts = {
            {TargetType::Plane, 4},
            {TargetType::Ship, 3},
            {TargetType::Missile, 2}
    };

    //sensorData.startSensor(LosAngeles);

    missionPlanner.setMission(LosAngeles);

    std::cout << "******** ---- [CommandAndControl] Mission Completed ---- ********" << std::endl;
}