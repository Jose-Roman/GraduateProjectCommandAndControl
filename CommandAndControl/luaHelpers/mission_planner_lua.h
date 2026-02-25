//
// Created by Jose Roman  on 2/19/26.
//

#ifndef __MISSION_PLANNER_LUA__
#define __MISSION_PLANNER_LUA__

#pragma once
#include "MissionPlanner.h"
#include <lua.hpp>

extern "C" int luaopen_mission_planner(lua_State *L);

#endif // __MISSION_PLANNER_LUA__

