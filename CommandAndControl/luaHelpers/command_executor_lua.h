//
// Created by Jose Roman  on 2/18/26.
//

#ifndef __COMMAND_EXECUTOR_LUA__
#define __COMMAND_EXECUTOR_LUA__
#include <lua.h>

#include "CommandExecutor.h"

//
// Created by Jose Roman on 2/18/26.
//

#pragma once

#include "CommandExecutor.h"

// Register a CommandExecutor instance with Lua
void registerCommandExecutor(CommandExecutor* executor);

#endif // __COMMAND_EXECUTOR_LUA__