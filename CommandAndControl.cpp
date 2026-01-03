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

void helloWorld() {
    std::cout << "Hello World from CommandAndControl!" << std::endl;
}

void runCommandAndControl() {

    std::cout << "---- Starting Command and Control System ----" << std::endl;

    // Create shared Messaging helper
    Messaging msg;

    // Create system components
    CommandExecutor commandExecutor(msg);
    SensorData sensorData(msg);
    TargetTracker targetTracker(msg);
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