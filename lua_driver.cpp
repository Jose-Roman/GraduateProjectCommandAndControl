//
// Created by Jose Roman  on 12/14/25.
//

#include <lua.hpp>
#include <iostream>
#include "CommandCore.h"

#include "CommandAndControl/GenerateScenario.h"
#include "CommandAndControl/Messaging.h"
#include "CommandAndControl/SensorData.h"
#include "CommandAndControl/TargetTracker.h"
#include "CommandAndControl/MissionPlanner.h"
#include "CommandAndControl/CommandExecutor.h"
#include "CommandAndControl/Geography.h"

int lua_send(lua_State* L) {
    // Get the first Lua argument as string
    const char* cmd = luaL_checkstring(L, 1);
    const char* payload = luaL_optstring(L, 2, "");

    auto result = command::send_command(cmd, payload);

    lua_newtable(L);

    lua_pushinteger(L, result.code);
    lua_setfield(L, -2, "code");

    lua_pushstring(L, result.message.c_str());
    lua_setfield(L, -2, "message");

    return 1; // number of return values
}

static MissionArea parseMissionArea(const std::string& area) {
    if (area == "LosAngeles") return MissionArea::LosAngeles;
    if (area == "NewYork") return MissionArea::NewYork;
    if (area == "Miami") return MissionArea::Miami;
    return MissionArea::LosAngeles;
}

static TargetType parseTargetType(const std::string &type) {
    if (type == "Plane") return TargetType::Plane;
    if (type == "Ship") return TargetType::Ship;
    if (type == "Missile") return TargetType::Missile;
    return TargetType::Plane;
}


static int lua_start_mission(lua_State* L) {
    std::cout << "---- Starting Command and Control Mission System ----" << std::endl;

    // Ensure argument is a table
    if (!lua_istable(L,1)) {
        return luaL_error(L, "start_mission expects a table");
    }

    // Read mission.name
    lua_getfield(L, 1, "name");
    std::string nameStr = lua_tostring(L, -1);
    lua_pop(L, 1);

    // Read mission.area
    lua_getfield(L, 1, "area");
    std::string areaStr = lua_tostring(L, -1);
    lua_pop(L, 1);

    // Read mission.duration
    lua_getfield(L, 1, "duration");
    int duration = static_cast<int>(lua_tointeger(L, -1));
    lua_pop(L, 1);

    // Create core systems
    Messaging msg;
    Geography geo;

    // Create system components
    SensorData sensorData(msg);
    TargetTracker targetTracker(msg, geo);
    MissionPlanner missionPlanner(msg, targetTracker);
    CommandExecutor commandExecutor(msg, targetTracker);
    GenerateScenario genScenStart(sensorData, geo, commandExecutor);

    // Initialize subscriptions for messaging system
    commandExecutor.initialize();
    sensorData.initialize();
    targetTracker.initialize();
    missionPlanner.initialize();

    // Build Mission
    Mission mission;
    mission.name = nameStr;
    mission.area = parseMissionArea(areaStr);
    mission.scenarioDuration = duration;


    // Read targets table
    lua_getfield(L, 1, "targets");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            std::string typeStr = lua_tostring(L, -2);
            int count = static_cast<int>(lua_tonumber(L, -1));
            TargetType type = parseTargetType(typeStr);
            mission.targetCounts[type] = count;

            lua_pop(L, 1); //pop value
        }
    }
    // pop targets table
    lua_pop(L, 1);

    // Run Mission
    genScenStart.setFullMission(mission);
    genScenStart.startScenario();

    std::cout << "******** ---- [CommandAndControl] Mission Completed ---- ********" << std::endl;

    return 0;
}

//extern "C" int luaopen_commandcore(lua_State* L) {
  //  command::initialize();
    //lua_newtable(L);
    //lua_pushcfunction(L, lua_send);
    //lua_setfield(L, -2, "send");

   // return 1;
//}

extern "C" int luaopen_commandcore(lua_State* L) {
    lua_newtable(L);
    lua_pushcfunction(L, lua_start_mission);
    lua_setfield(L, -2, "start_mission");

    return 1;
}