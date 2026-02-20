//
// Created by Jose Roman  on 2/19/26.
//

#include <lua.hpp>
#include "MissionPlanner.h"
#include "Geography.h"
#include "mission_planner_lua.h"
#include <iostream>

// MissionPlanner Functions
// MissionPlanner(Messaging& messaging, TargetTracker& tracker);
// initialize();
// setMission(const Mission& mission);
// planMission(Target& track);

Messaging msg;
Geography geo;

TargetTracker targetTracker(msg, geo);
MissionPlanner mission_planner(msg, targetTracker);

static bool g_initialized = false;

static void ensureInitialized() {
    if(!g_initialized) {
        targetTracker.initialize();
        mission_planner.initialize();

        g_initialized = true;

        std::cout << "[MissionPlanner Lua] initialized" << std::endl;
    }
}

// mission_planner.initialize()
static int lua_mission_planner_initialize(lua_State* L) {
    ensureInitialized();
    return 0;
}

// mission_planner.set_mission("MissionName")
static int lua_mission_planner_set_mission(lua_State* L) {
    ensureInitialized();

    const char* missionName = luaL_checkstring(L,1);

    Mission msn;
    msn.name = missionName;

    // Example defaults
    msn.area = MissionArea::LosAngeles;
    msn.targetCounts = {
            {TargetType::Plane, 1},
            {TargetType::Ship, 1},
            {TargetType::Missile, 1}
    };

    std::cout << "[MissionPlanner Lua] setting mission" << std::endl;

    mission_planner.setMission(msn);

    return 0;
}

// mission_planner.simulate_target_update("serialized_target)
static int lua_mission_planner_simulate_target(lua_State* L) {
    ensureInitialized();

    const char* payload = luaL_checkstring(L,1);

    Message newMsg;
    newMsg.topic = "target.update";
    newMsg.payload = payload;
    newMsg.source = "MissionPlanner Lua";
    newMsg.timestamp = 10;

    std::cout << "[MissionPlanner Lua] simulating target update" << std::endl;

    msg.publish(newMsg);

    return 0;
}

// Lua function table
static const luaL_Reg MissionPLannerFunctions[] = {
    {"initialize", lua_mission_planner_initialize},
    {"set_mission", lua_mission_planner_set_mission},
    {"simulate_target", lua_mission_planner_simulate_target},
    {nullptr,  nullptr}
};


// Lua entry point

extern "C" int luaopen_mission_planner(lua_State *L) {
    luaL_newlib(L, MissionPLannerFunctions);
    return 1;
}

