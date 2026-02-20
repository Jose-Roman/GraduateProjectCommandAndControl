//
// Created by Jose Roman  on 2/19/26.
//

#include "target_tracker_lua.h"

#include <lua.hpp>
#include "TargetTracker.h"
#include "Messaging.h"
#include "Geography.h"
#include <iostream>

// TargetTracker functions
// TargetTracker(Messaging& messaging, Geography& geography);
// initialize();
// trackTarget(MissionArea area, TargetType track);
// updateTrack(int targetId, int duration);
// getUpdateInterval(TargetType type);
// serializeTarget(const Target& target);
// deserializeTarget(const std::string& payload);


// Create standalone instances
static Messaging msg;
static Geography geo;
static TargetTracker tracker(msg, geo);

static bool g_initialized = false;

// Ensure initialized
static void ensureInitialized() {
    if (!g_initialized) {
        tracker.initialize();
        g_initialized = true;
        std::cout << "[TargetTracker Lua] initialized" << std::endl;
    }
}

// tracker.initialize()
static int lua_target_tracker_initialize(lua_State *L) {
    ensureInitialized();
    return 0;
}

// tracker.simulate_sensor(area, type)
static int lua_target_tracker_simulate_sensor(lua_State *L) {
    ensureInitialized();
    const char* area = luaL_checkstring(L, 1);
    const char* type = luaL_checkstring(L, 2);

    std::string payload = std::string(area) + ":" + type;

    Message newMsg;
    newMsg.topic = "sensor.data";
    newMsg.payload = payload;
    newMsg.source = "TargetTracker Lua";
    newMsg.timestamp = 15;

    std::cout << "[TargetTracker Lua] simulating sensor data:"
        << payload << std::endl;

    msg.publish(newMsg);

    return 0;
}

// tracker.simulate_detection(area, type)
static int lua_target_tracker_simulate_detection(lua_State *L) {
    ensureInitialized();
    const char* area = luaL_checkstring(L, 1);
    const char* type = luaL_checkstring(L, 2);

    std::string payload = std::string(area) + ":" + type;

    Message newMsg;
    newMsg.topic = "sensor.target.detected";
    newMsg.payload = payload;
    newMsg.source = "TargetTracker Lua";
    newMsg.timestamp = 20;

    std::cout << "[TargetTracker Lua] simulating detection:"
        << payload << std::endl;

    msg.publish(newMsg);

    return 0;
}

// Lua function table
static const luaL_Reg TargetTrackerFunctions[] = {
    {"initialize", lua_target_tracker_initialize},
    {"simulate_sensor", lua_target_tracker_simulate_sensor},
    {"simulate_detection", lua_target_tracker_simulate_detection},
    {nullptr, nullptr}
};

// Entry point

extern "C" int luaopen_target_tracker(lua_State *L) {
    luaL_newlib(L, TargetTrackerFunctions);
    return 1;
}