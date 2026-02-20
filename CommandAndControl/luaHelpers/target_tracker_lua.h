//
// Created by Jose Roman  on 2/19/26.
//

#ifndef __TARGET_TRACKER_LUA__
#define __TARGET_TRACKER_LUA__

#include "TargetTracker.h"
#include <lua.hpp>
#pragma once

extern "C" int luaopen_target_tracker(lua_State *L);

#endif // __TARGET_TRACKER_LUA__