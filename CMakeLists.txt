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
        CommandAndControl/GenerateScenario.h)

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