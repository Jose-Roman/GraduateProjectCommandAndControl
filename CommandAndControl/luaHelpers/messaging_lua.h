//
// Created by Jose Roman  on 2/20/26.
//

#ifndef __MESSAGING_LUA__
#define __MESSAGING_LUA__

#include <lua.hpp>
#include "Messaging.h"

extern "C" int luaopen_messaging(lua_State *L);

#endif // __MESSAGING_LUA__