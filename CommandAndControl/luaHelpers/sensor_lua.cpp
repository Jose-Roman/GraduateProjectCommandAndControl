//
// Created by Jose Roman  on 2/17/26.
//

#include "SensorData.h"
#include <lua.hpp>
#include "MissionPlanner.h"
#include <iostream>
#include <lauxlib.h>

#include "Messaging.h"

static Messaging g_msg;
static SensorData g_sensor_instance(g_msg);

// SensorData functions
// SensorData(Messaging& messaging);
// initialize();
// readSensor() const;
// publishSensorData();
// startSensor(const Mission& mission);

// global pointer to activate sensor system
static SensorData* g_sensor = nullptr;

// register sensor
void registerSensor(SensorData* sensor) {
    g_sensor = sensor;
}

// sensor.initialize()
static int lua_sensor_initialize(lua_State* L) {
    if (!g_sensor) {
        return luaL_error (L, "SensorData not initialized");
    }

    g_sensor->initialize();
    return 0;
}

// sensor.publish()
static int lua_sensor_publish(lua_State* L) {
    if (!g_sensor) {
        return luaL_error (L, "SensorData not initialized");
    }
    g_sensor->publishSensorData();

    return 0;
}

// sensor.read()
static int lua_sensor_read(lua_State* L) {
    if (!g_sensor) {
        return luaL_error (L, "SensorData not initialized");
    }
    SensorReading reading = g_sensor->readSensor();
    lua_newtable (L);
    lua_pushstring(L,"name");
    lua_pushstring(L, reading.sensorName.c_str());
    lua_settable (L, -3);

    lua_pushstring(L,"value");
    lua_pushnumber(L,reading.value);
    lua_settable (L, -3);

    return 1;
}

// sensor.start()
static int lua_sensor_start(lua_State* L) {
    if (!g_sensor) {
        return luaL_error(L, "SensorData not registered");
    }

    return luaL_error(L,
        "sensor.start() cannot be called directly. "
        "Use command.start_mission()");
}


// sensor.start__mission()
static int lua_sensor_start_mission(lua_State* L) {
    if (!g_sensor) {
        return luaL_error (L, "SensorData not initialized");
    }

    const char* missionName = luaL_checkstring(L,1);

    Mission mission;
    mission.name = missionName;
    mission.area = MissionArea::LosAngeles; //test default

    mission.targetCounts = {
        {TargetType::Plane, 10},
        {TargetType::Ship, 1},
        {TargetType::Missile, 1}
    };

    std::cout << "[Lua Sensor] Triggered for mission: "<<
        missionName << std::endl;

    g_sensor->publishSensorData();

    return 0;
}

// Lua function table
static const luaL_Reg SensorFunctions[] = {
    {"initialize", lua_sensor_initialize},
    {"publish", lua_sensor_publish},
    {"read", lua_sensor_read},
    {"start", lua_sensor_start},
    {"start_mission", lua_sensor_start_mission},
    {nullptr, nullptr}
};

// Entry point
extern "C" int luaopen_sensor(lua_State* L)
{
    // assign global pointer
    registerSensor(&g_sensor_instance);

    luaL_newlib(L, SensorFunctions);
    return 1;
}