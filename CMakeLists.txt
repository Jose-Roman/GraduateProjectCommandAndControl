cmake_minimum_required(VERSION 4.1)
project(GraduateProject)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake where to find Lua headers
include_directories(/opt/homebrew/opt/lua/include/lua5.4)

# Tell CMake where to find Lua library
link_directories(/opt/homebrew/opt/lua/lib)

#### LUA

# ---- Core Command & Control Library ----
add_library(CommandAndControlLib STATIC
        CommandAndControl/Messaging.cpp
        CommandAndControl/SensorData.cpp
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/MissionPlanner.cpp
        CommandAndControl/CommandExecutor.cpp
        CommandAndControl/GenerateScenario.cpp
        CommandAndControl/Geography.cpp
        CommandAndControl/luaHelpers/sensor_lua.cpp
        CommandAndControl/luaHelpers/sensor_lua.h
        CommandAndControl/luaHelpers/command_executor_lua.cpp
        CommandAndControl/luaHelpers/command_executor_lua.h
        CommandAndControl/luaHelpers/mission_planner_lua.cpp
        CommandAndControl/luaHelpers/mission_planner_lua.h
        CommandAndControl/luaHelpers/target_tracker_lua.cpp
        CommandAndControl/luaHelpers/target_tracker_lua.h
        CommandAndControl/luaHelpers/messaging_lua.cpp
        CommandAndControl/luaHelpers/messaging_lua.h
        CommandAndControl/luaHelpers/geography_lua.cpp
        CommandAndControl/luaHelpers/geography_lua.h
        CommandAndControl/luaHelpers/generate_scenario_lua.cpp
        CommandAndControl/luaHelpers/generate_scenario_lua.h
)

target_include_directories(CommandAndControlLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/CommandAndControl
)

# ---- Lua Command Core (Lua module) ----
add_library(commandcore SHARED
        CommandCore.cpp
        lua_driver.cpp
)

target_include_directories(commandcore PRIVATE
        ${LUA_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(commandcore
        lua
        CommandAndControlLib
)

set_target_properties(commandcore PROPERTIES
        PREFIX ""
        OUTPUT_NAME "commandcore"
)

# Sensor Module
add_library(sensor SHARED
            CommandAndControl/luaHelpers/sensor_lua.cpp
            CommandAndControl/SensorData.cpp
            CommandAndControl/Messaging.cpp)
target_link_libraries(sensor
        lua
        CommandAndControlLib)

set_target_properties(sensor PROPERTIES
        PREFIX ""
        OUTPUT_NAME "sensor"
)
# End Sensor Module

## Command Executor Module

add_library(command_executor SHARED
        CommandAndControl/luaHelpers/command_executor_lua.cpp
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Geography.cpp
        CommandAndControl/CommandExecutor.cpp
)

target_link_libraries(command_executor
        lua
        CommandAndControlLib)

set_target_properties(command_executor PROPERTIES
        PREFIX ""
        OUTPUT_NAME "command_executor"
)

## End Command Executor Module

## Mission Planner Module

add_library(mission_planner SHARED
        CommandAndControl/luaHelpers/mission_planner_lua.cpp
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Geography.cpp
        CommandAndControl/MissionPlanner.cpp)

target_link_libraries(mission_planner
        lua
        CommandAndControlLib)

set_target_properties(mission_planner PROPERTIES
        PREFIX ""
        OUTPUT_NAME "mission_planner"
)

## End Mission Planner Module

## Target Tracker Module

add_library(target_tracker SHARED
        CommandAndControl/luaHelpers/target_tracker_lua.cpp
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Geography.cpp)

target_link_libraries(target_tracker
        lua
        CommandAndControlLib)

set_target_properties(target_tracker PROPERTIES
        PREFIX ""
        OUTPUT_NAME "target_tracker"
)

## End Target Tracker Module

## Messaging Module

add_library(messaging SHARED
        CommandAndControl/luaHelpers/messaging_lua.cpp
        CommandAndControl/Messaging.cpp)

target_link_libraries(messaging
        lua
        CommandAndControlLib)

set_target_properties(messaging PROPERTIES
        PREFIX ""
        OUTPUT_NAME "messaging"
)

## End Messaging Module

## Geography Module

add_library(geography SHARED
        CommandAndControl/luaHelpers/geography_lua.cpp
        CommandAndControl/Geography.cpp)

target_link_libraries(geography
        lua
        CommandAndControlLib)

set_target_properties(geography PROPERTIES
        PREFIX ""
        OUTPUT_NAME "geography"
)

## End Geography Module


## Generate Scenario Module

add_library(generate_scenario SHARED
        CommandAndControl/luaHelpers/generate_scenario_lua.cpp
        CommandAndControl/GenerateScenario.cpp
        CommandAndControl/SensorData.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Geography.cpp
        CommandAndControl/CommandExecutor.cpp
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/luaHelpers/generate_scenario_lua.h)

target_link_libraries(generate_scenario
        lua
        CommandAndControlLib)

set_target_properties(generate_scenario PROPERTIES
        PREFIX ""
        OUTPUT_NAME "generate_scenario"
)

## End Generate Scenario Module

#### LUA

##### ADD GOOGLE TESTS
find_package(GTest REQUIRED)
#####

add_executable(GraduateProject main.cpp
        CommandAndControl.cpp
        CommandAndControl.h
        CommandCore.cpp
        CommandCore.h
        lua_driver.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Messaging.h
        CommandAndControl/MissionPlanner.cpp
        CommandAndControl/MissionPlanner.h
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/TargetTracker.h
        CommandAndControl/SensorData.cpp
        CommandAndControl/SensorData.h
        CommandAndControl/CommandExecutor.cpp
        CommandAndControl/CommandExecutor.h
        CommandAndControl/Geography.cpp
        CommandAndControl/Geography.h
        CommandAndControl/Types.h
        CommandAndControl/GenerateScenario.cpp
        CommandAndControl/GenerateScenario.h
        CommandAndControl/luaHelpers/sensor_lua.cpp
        CommandAndControl/luaHelpers/sensor_lua.h
        CommandAndControl/luaHelpers/command_executor_lua.cpp
        CommandAndControl/luaHelpers/command_executor_lua.h
        CommandAndControl/luaHelpers/mission_planner_lua.cpp
        CommandAndControl/luaHelpers/mission_planner_lua.h
        CommandAndControl/luaHelpers/target_tracker_lua.cpp
        CommandAndControl/luaHelpers/target_tracker_lua.h
        CommandAndControl/luaHelpers/messaging_lua.cpp
        CommandAndControl/luaHelpers/messaging_lua.h
        CommandAndControl/luaHelpers/geography_lua.cpp
        CommandAndControl/luaHelpers/geography_lua.h
        CommandAndControl/luaHelpers/generate_scenario_lua.cpp
        CommandAndControl/luaHelpers/generate_scenario_lua.h)

add_executable(UnitTests
        CommandAndControl/test/TargetTrackerTest.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Messaging.h
        CommandAndControl/MissionPlanner.cpp
        CommandAndControl/MissionPlanner.h
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/TargetTracker.h
        CommandAndControl/SensorData.cpp
        CommandAndControl/SensorData.h
        CommandAndControl/CommandExecutor.cpp
        CommandAndControl/CommandExecutor.h
        CommandAndControl/Geography.cpp
        CommandAndControl/Geography.h
        CommandAndControl/Types.h
        CommandAndControl/GenerateScenario.cpp
        CommandAndControl/GenerateScenario.h
        CommandAndControl/test/CommandExecutorTest.cpp
        CommandAndControl/test/GenerateScenarioTest.cpp
        CommandAndControl/test/GeographyTest.cpp
        CommandAndControl/test/MessagingTest.cpp
        CommandAndControl/test/SensorDataTest.cpp
        CommandAndControl/test/MissionPlannerTest.cpp)


target_include_directories(GraduateProject PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/CommandAndControl)

target_include_directories(UnitTests PRIVATE CommandAndControl)

target_link_libraries(UnitTests
        GTest::gtest
        GTest::gtest_main
)

# Link Lua library AFTER add_executable
target_link_libraries(GraduateProject lua)

target_link_libraries(GraduateProject
        CommandAndControlLib
)

enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)


#### PYTHON

find_package(pybind11 REQUIRED)

pybind11_add_module(command_system
        CommandAndControl/pythonHelpers/python_c_hello_world.cpp
)

add_library(command_control_py
        CommandAndControl/Messaging.cpp
        CommandAndControl/Messaging.h
        CommandAndControl/MissionPlanner.cpp
        CommandAndControl/MissionPlanner.h
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/TargetTracker.h
        CommandAndControl/SensorData.cpp
        CommandAndControl/SensorData.h
        CommandAndControl/CommandExecutor.cpp
        CommandAndControl/CommandExecutor.h
        CommandAndControl/Geography.cpp
        CommandAndControl/Geography.h
        CommandAndControl/Types.h
        CommandAndControl/GenerateScenario.cpp
        CommandAndControl/GenerateScenario.h
)

target_link_libraries(GraduateProject
        command_control_py
)


### COMMAND EXECUTOR PY
pybind11_add_module(command_executor_py
        CommandAndControl/pythonHelpers/python_command_executor.cpp
)

target_include_directories(command_executor_py
        PRIVATE
        ${PROJECT_SOURCE_DIR}/CommandAndControl
)

target_link_libraries(command_executor_py
        PRIVATE command_control_py
)

### COMMAND EXECUTOR PY


### GENERATE SCENARIO PY
pybind11_add_module(generate_scenario_py
        CommandAndControl/pythonHelpers/python_generate_scenario.cpp
)

target_include_directories(generate_scenario_py
        PRIVATE
        ${PROJECT_SOURCE_DIR}/CommandAndControl
)

target_link_libraries(generate_scenario_py
        PRIVATE command_control_py
)

### GENERATE SCENARIO PY


### GEOGRAPHY PY
pybind11_add_module(geography_py
        CommandAndControl/pythonHelpers/python_geography.cpp
)

target_include_directories(geography_py
        PRIVATE
        ${PROJECT_SOURCE_DIR}/CommandAndControl
)

target_link_libraries(geography_py
        PRIVATE command_control_py
)

### GEOGRAPHY PY


### MESSAGING PY
pybind11_add_module(messaging_py
        CommandAndControl/pythonHelpers/python_messaging.cpp
)

target_include_directories(messaging_py
        PRIVATE
        ${PROJECT_SOURCE_DIR}/CommandAndControl
)

target_link_libraries(messaging_py
        PRIVATE command_control_py
)

### MESSAGING PY


### MISSION_PLANNING PY
pybind11_add_module(mission_planner_py
        CommandAndControl/pythonHelpers/python_mission_planner.cpp
)

target_include_directories(mission_planner_py
        PRIVATE
        ${PROJECT_SOURCE_DIR}/CommandAndControl
)

target_link_libraries(mission_planner_py
        PRIVATE command_control_py
)

### MISSION_PLANNING PY



#### PYTHON