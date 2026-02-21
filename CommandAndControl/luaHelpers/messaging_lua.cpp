//
// Created by Jose Roman  on 2/20/26.
//

#include "messaging_lua.h"
#include <lua.hpp>
#include "Messaging.h"
#include <iostream>

// Global instance
static Messaging g_messaging;

// Messaging Functions
// publish(Message& msg);
// subscribe(const std::string& topic, Callback cb);

// messaging.publish(topic, payload, source)
static int lua_messaging_publish(lua_State *L) {
    if (!lua_istable(L,1))
        return luaL_error(L, "'publish expects a table");

    Message msg;
    lua_getfield(L,1,"topic");
    msg.topic = lua_tostring(L,-1);
    lua_pop(L,1);

    lua_getfield(L,1,"payload");
    msg.payload = lua_tostring(L,-1);
    lua_pop(L,1);

    lua_getfield(L, 1, "source");
    msg.source = lua_tostring(L,-1);
    lua_pop(L,1);


    g_messaging.publish(msg);

    lua_newtable(L);

    lua_pushinteger(L, msg.messageId);
    lua_setfield(L,-2,"messageId");

    lua_pushinteger(L, msg.timestamp);
    lua_setfield(L,-2,"timestamp");

    return 1;
}


// messaging.subscribe()
static int lua_messaging_subscribe(lua_State *L) {
    const char *topic = lua_tostring(L, 1);

    g_messaging.subscribe(topic,
        [](const Message& msg) {
            std::cout
            << "[Lua Subscriber]"
            << msg.topic
            << " | payload: " << msg.payload
            << " | source: " << msg.source
            << std::endl;
        });
    return 0;
}

// Lua function table
static const luaL_Reg MessagingFunctions[] = {
    {"publish", lua_messaging_publish},
    {"subscribe", lua_messaging_subscribe},
    {nullptr, nullptr}
};

extern "C" int luaopen_messaging(lua_State *L) {
    luaL_newlib(L, MessagingFunctions);
    return 1;
}