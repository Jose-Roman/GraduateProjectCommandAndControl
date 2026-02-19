//
// Created by Jose Roman  on 2/18/26.
//

#include <lua.hpp>
#include <lauxlib.h>
#include "command_executor_lua.h"
#include <iostream>
#include "CommandExecutor.h"
#include "Messaging.h"
#include "TargetTracker.h"
#include "Geography.h"


// CommandExecutor functions
// initialize();
// executeCommand(const std::string& command);
// setScenarioDuration(int scenarioDuration);

Messaging msg;
Geography geo;
TargetTracker targetTracker(msg, geo);
CommandExecutor g_command_executor_instance(msg, targetTracker);

// global pointer
static CommandExecutor* g_command_executor = nullptr;

// register executor
void registerCommandExecutor(CommandExecutor* command_executor) {
    g_command_executor = command_executor;
}

// executor.initialize()
static int lua_command_executor_initialize(lua_State* L) {
    if (!g_command_executor)
        return luaL_error(L, "Command Executor not registered");

    g_command_executor->initialize();

    return 0;
}

// executor.execute_command()
static int lua_execute_command(lua_State* L) {
    if (!g_command_executor)
        return luaL_error(L, "Command Executor not registered");

    const char* command = luaL_checkstring(L, 1);
    g_command_executor->executeCommand(command);

    return 0;
}

//executor.set_duration()
static int lua_set_duration(lua_State* L) {
    if (!g_command_executor)
        return luaL_error(L, "Command Executor not registered");

    int duration = luaL_checkinteger(L, 1);
    g_command_executor->setScenarioDuration(duration);

    return 0;
}

static const luaL_Reg CommandExecutorFunctions[] = {
    {"initialize", lua_command_executor_initialize},
    {"execute_command", lua_execute_command},
    {"set_duration", lua_set_duration},
    {nullptr, nullptr}
};

extern "C" int luaopen_command_executor(lua_State* L) {
    // assign global pointer
    registerCommandExecutor(&g_command_executor_instance);

    luaL_newlib(L, CommandExecutorFunctions);
    return 1;
}
