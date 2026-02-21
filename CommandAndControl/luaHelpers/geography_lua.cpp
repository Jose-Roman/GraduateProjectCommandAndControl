//
// Created by Jose Roman  on 2/20/26.
//

#include "geography_lua.h"
#include "Geography.h"
#include <lua.hpp>

// Geography Functions
//  getGioBounds(MissionArea& area);
// GeoKinematics getGioKinematics(TargetType& track);
// double randomDouble(double min, double max);
// static sensorLocation getSensorLocation(MissionArea& area);
// MissionArea parseMissionArea(const std::string& areaStr);

// Global Geography instance
static Geography g_geo;

// Helpers
static MissionArea parseMissionAreaLua(const char* area) {
    return g_geo.parseMissionArea(area);
}

static TargetType parseTargetTypeLua(const char* type) {
    if (strcmp(type, "Plane") == 0) return TargetType::Plane;
    if (strcmp(type, "Ship") == 0) return TargetType::Ship;
    if (strcmp(type, "Missile") == 0) return TargetType::Missile;

    return TargetType::Plane;
}

// geography.get_bounds(MissionArea)
static int lua_geo_get_bounds(lua_State* L) {
    const char* areaStr= luaL_checkstring(L, 1);

    MissionArea area= parseMissionAreaLua(areaStr);

    GeoBounds bounds = g_geo.getGioBounds(area);

    lua_newtable(L);

    lua_pushnumber(L, bounds.minLatitude);
    lua_setfield(L, -2, "minLatitude");

    lua_pushnumber(L, bounds.maxLatitude);
    lua_setfield(L, -2, "maxLatitude");

    lua_pushnumber(L, bounds.minLongitude);
    lua_setfield(L, -2, "minLongitude");

    lua_pushnumber(L, bounds.maxLongitude);
    lua_setfield(L, -2, "maxLongitude");

    return 1;
}

// geography.get_kinematics(TargetType)
static int lua_get_geo_kinematics(lua_State* L) {
    const char* typeStr = luaL_checkstring(L, 1);

    TargetType type = parseTargetTypeLua(typeStr);

    GeoKinematics kin = g_geo.getGioKinematics(type);

    lua_newtable(L);

    lua_pushnumber(L, kin.minAltitude);
    lua_setfield(L, -2, "minAltitude");

    lua_pushnumber(L, kin.maxAltitude);
    lua_setfield(L, -2, "maxAltitude");

    lua_pushnumber(L, kin.minSpeed);
    lua_setfield(L, -2, "minSpeed");

    lua_pushnumber(L, kin.maxSpeed);
    lua_setfield(L, -2, "maxSpeed");

    return 1;
}

// geography.random(min, max)
static int lua_geo_random(lua_State* L) {
    double min = luaL_checknumber(L, 1);
    double max = luaL_checknumber(L, 2);

    double value = g_geo.randomDouble(min, max);

    lua_pushnumber(L, value);

    return 1;
}

// geography.get_sensor_location(MissionArea)
static int lua_geo_get_sensor_location(lua_State* L) {
    const char* areaStr= luaL_checkstring(L, 1);

    MissionArea area= parseMissionAreaLua(areaStr);

    sensorLocation loc = g_geo.getSensorLocation(area);

    lua_newtable(L);

    lua_pushnumber(L, loc.latitude);
    lua_setfield(L, -2, "latitude");

    lua_pushnumber(L, loc.longitude);
    lua_setfield(L, -2, "longitude");

    return 1;
}

// geography.parse_area(MissionArea)
static int lua_geo_parse_area(lua_State* L) {
    const char* areaStr= luaL_checkstring(L, 1);
    MissionArea area= parseMissionAreaLua(areaStr);

    lua_pushinteger(L, static_cast<int>(area));

    return 1;
}

// Lua function table
static const luaL_Reg GeographyFunctions[] = {
    {"get_bounds", lua_geo_get_bounds},
    {"get_kinematics", lua_get_geo_kinematics},
    {"random", lua_geo_random},
    {"get_sensor_location", lua_geo_get_sensor_location},
    {"parse_area", lua_geo_parse_area},
    {nullptr, nullptr}
};

// Entry point
extern "C" int luaopen_geography(lua_State *L) {
    luaL_newlib(L, GeographyFunctions);
    return 1;
}