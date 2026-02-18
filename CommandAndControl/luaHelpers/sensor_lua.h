//
// Created by Jose Roman  on 2/17/26.
//

#ifndef __SENSOR_LUA__
#define __SENSOR_LUA__
#include "SensorData.h"
#include <lua.hpp>
#pragma once

// Lua entry pint
int luaopen_sensor(lua_State* L);

// Registers the active SensorData instance
void registerSensor(SensorData* sensor);

#endif //__SENSOR_LUA__