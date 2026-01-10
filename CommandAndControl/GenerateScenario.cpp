//
// Created by Jose Roman  on 1/9/26.
//

#include "GenerateScenario.h"
#include "MissionPlanner.h"
#include "SensorData.h"
#include <iostream>

GenerateScenario::GenerateScenario(MissionPlanner &planner, SensorData &sensor)
    : planner_(planner), sensor_(sensor) {}

void GenerateScenario::setLocation(MissionArea area) {
    area_ = area;
}

void GenerateScenario::setTargetCount(TargetType type, int count) {
    targetCounts_[type] = count;
}

void GenerateScenario::startScenario() {
    std::cout << "[GenerateScenario] Starting scenario ..." << std::endl;

    Mission startMission;
    startMission.area = area_;
    startMission.targetCounts = targetCounts_;

    planner_.setMission(startMission);

    sensor_.startSensor(startMission);
}
