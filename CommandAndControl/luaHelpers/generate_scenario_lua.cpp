//
// Created by Jose Roman  on 2/20/26.
//

#include <lua.hpp>
#include "generate_scenario_lua.h"

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

static Mission g_mission;

// helpers
static MissionArea parseMissionAreaLua(const std::string& area) {
    if (area == "LosAngeles") return MissionArea::LosAngeles;
    if (area == "Miami") return MissionArea::Miami;
    if (area == "NewYork") return MissionArea::NewYork;

    return MissionArea::LosAngeles;
}

static TargetType parseTargetTypeLua(const std::string& type) {
    if (type == "Plane") return TargetType::Plane;
    if (type == "Ship") return TargetType::Ship;
    if (type == "Missile") return TargetType::Missile;

    return TargetType::Plane;
}

// scenario.set_mission
static int lua_scenario_set_mission(lua_State* L) {
    if (!lua_istable(L, 1))
        return luaL_error(L, "Expected mission table");

    // name
    lua_getfield(L, 1, "name");
    g_mission.name = lua_tostring(L, -1);
    lua_pop(L, 1);

    // area
    lua_getfield(L, 1, "area");
    std::string areaStr = lua_tostring(L, -1);
    lua_pop(L, 1);

    g_mission.area = parseMissionAreaLua(areaStr);

    // duration
    lua_getfield(L, 1, "duration");
    g_mission.scenarioDuration = (int)luaL_checknumber(L, -1);
    lua_pop(L, 1);

    // targets table
    lua_getfield(L, 1, "targets");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            std::string typeStr = luaL_checkstring(L, -2);
            int count = (int)luaL_checknumber(L, -1);
            g_mission.targetCounts[parseTargetTypeLua(typeStr)] = count;
            lua_pop(L, 1);
        }
    }

    lua_pop(L, 1);
    g_scenario.setFullMission(g_mission);
    std::cout << "[Generate Scenario Lua] Mission Configured" << std::endl;
    return 0;
}

// scenario.start()
static int lua_scenario_start(lua_State* L) {
    std::cout << "[Generate Scenario Lua] Starting Scenario ... " << std::endl;
    g_sensor.initialize();
    g_tracker.initialize();
    g_command_executor.initialize();
    g_scenario.startScenario();

    return 0;
}

// Lua function table
static const luaL_Reg GenerateScenarioFunctions[] = {
    {"set_mission", lua_scenario_set_mission},
    {"start", lua_scenario_start},
    {nullptr, nullptr}
};

// Entry point
extern "C" int luaopen_generate_scenario(lua_State* L) {
    luaL_newlib(L,GenerateScenarioFunctions);
    return 1;
}