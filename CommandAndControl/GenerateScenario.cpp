//
// Created by Jose Roman  on 1/9/26.
//

#include "GenerateScenario.h"
#include "SensorData.h"
#include <iostream>


GenerateScenario::GenerateScenario(SensorData& sensor) : sensor_(sensor) {}

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

    sensor_.startSensor(mission_);
}
