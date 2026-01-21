//
// Created by Jose Roman  on 1/9/26.
//

#include "GenerateScenario.h"
#include "SensorData.h"
#include <iostream>

#include "Geography.h"


GenerateScenario::GenerateScenario(SensorData& sensor, Geography& geography_) : sensor_(sensor),
    geography_(geography_) {}

void GenerateScenario::setMissionArea(MissionArea area) {
    mission_.area = area;
}

void GenerateScenario::setTargets(const std::map<TargetType, int>& targets) {
    mission_.targetCounts = targets;
}

void GenerateScenario::setMissionName(std::string name) {
    mission_.name = name;
}

void GenerateScenario::startScenario() {
    std::cout << "[GenerateScenario] Starting Scenario for " << mission_.name << std::endl;

    sensorLocation sensorLoc = geography_.getSensorLocation(mission_.area);

    std::cout << "[GenerateScenario] Sensor Location: at ("
                << sensorLoc.latitude << ", "
                << sensorLoc.longitude << ")"
                << std::endl;

    sensor_.startSensor(mission_);
}
