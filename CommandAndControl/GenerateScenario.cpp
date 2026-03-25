//
// Created by Jose Roman  on 1/9/26.
//

#include "GenerateScenario.h"
#include "SensorData.h"
#include <iostream>

#include "Geography.h"

//
// Created by Jose Roman  on 1/9/26.
//

#include "GenerateScenario.h"
#include "SensorData.h"
#include <iostream>

#include "Geography.h"

/**
 * Constructs a GenerateScenario instance.
 *
 * The GenerateScenario component serves as the orchestration layer for
 * initializing and executing a full mission scenario. It coordinates
 * between the SensorData, Geography, and CommandExecutor components.
 */
GenerateScenario::GenerateScenario(SensorData& sensor, Geography& geography, CommandExecutor& commandExecutor) : sensor_(sensor),
    geography_(geography), commandExecutor_(commandExecutor) {
}

/**
 * Configures the scenario with a complete mission definition.
 *
 * Stores the mission configuration and propagates the scenario duration
 * to the CommandExecutor. This ensures that all downstream components
 * operate with consistent timing constraints for simulation.
 */
void GenerateScenario::setFullMission(Mission newMission) {
    mission_ = newMission;
    commandExecutor_.setScenarioDuration(mission_.scenarioDuration);
}

/**
 * Starts execution of the configured mission scenario.
 *
 * This function acts as the entry point for the simulation.
 * It triggers the SensorData component to begin generating
 * sensor events.
 *
 * These sensor events drive the rest of the system through the
 * event-driven messaging pipeline:
 *
 * SensorData → TargetTracker → MissionPlanner → CommandExecutor
 */
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
