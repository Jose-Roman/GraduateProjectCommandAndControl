//
// Created by Jose Roman  on 1/9/26.
//

#include "GenerateScenario.h"
#include "SensorData.h"
#include <iostream>

#include "Geography.h"


GenerateScenario::GenerateScenario(SensorData& sensor, Geography& geography, CommandExecutor& commandExecutor) : sensor_(sensor),
    geography_(geography), commandExecutor_(commandExecutor) {
}


void GenerateScenario::setFullMission(Mission newMission) {
    mission_ = newMission;
    commandExecutor_.setScenarioDuration(mission_.scenarioDuration);
}

void GenerateScenario::startScenario() {
    std::cout << "[GenerateScenario] Starting Scenario for " << mission_.name << std::endl;

    sensorLocation sensorLoc = geography_.getSensorLocation(mission_.area);

    std::cout << "[GenerateScenario] Sensor Location: at ("
                << sensorLoc.latitude << ", "
                << sensorLoc.longitude << ")"
                << std::endl;

    std::cout << "[GenerateScenario] Scenario Duration: " << mission_.scenarioDuration << std::endl;

    sensor_.startSensor(mission_);
}
