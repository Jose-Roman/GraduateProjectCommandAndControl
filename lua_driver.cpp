//
// Created by Jose Roman  on 12/14/25.
//

#include <lua.hpp>
#include "CommandCore.h"

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

extern "C" int luaopen_commandcore(lua_State* L) {
    command::initialize();
    lua_newtable(L);
    lua_pushcfunction(L, lua_send);
    lua_setfield(L, -2, "send");

    return 1;
}