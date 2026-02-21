//
// Created by Jose Roman  on 2/20/26.
//

#include <lua.hpp>
#include "generate_scenario.h"

#include "GenerateScenario.h"
#include "SensorData.h"
#include "Messaging.h"
#include "Geography.h"
#include "CommandExecutor.h"
#include "TargetTracker.h"
#include "MissionPlanner.h"

#include <iostream>

// GenerateScenario Functions
//explicit GenerateScenario(SensorData& sensor, Geography& geography, CommandExecutor& commandExecutor);

// void setFullMission(Mission newMission);
// void startScenario();


// Global instances
static Messaging g_messaging;
static Geography g_geography;
static TargetTracker g_tracker(g_messaging, g_geography);
static CommandExecutor g_command_executor(g_messaging, g_tracker);
static SensorData g_sensor(g_messaging);
static GenerateScenario g_scenario(g_sensor, g_geography, g_command_executor);

// helpers


// scenario.set_mission



// scenario.start()


// Lua function table


// Entry point