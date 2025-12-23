cmake_minimum_required(VERSION 4.1)
project(GraduateProject)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake where to find Lua headers
include_directories(/opt/homebrew/opt/lua/include/lua5.4)

# Tell CMake where to find Lua library
link_directories(/opt/homebrew/opt/lua/lib)

add_executable(GraduateProject main.cpp
        CommandAndControl.cpp
        CommandAndControl.h
        CommandCore.cpp
        CommandCore.h
        lua_driver.cpp
        main.cpp
        main.cpp
        main.cpp
        CommandAndControl/Messaging.cpp
        CommandAndControl/Messaging.h
        CommandAndControl/MissionPlanner.cpp
        CommandAndControl/MissionPlanner.h
        CommandAndControl/TargetTracker.cpp
        CommandAndControl/TargetTracker.h
        CommandAndControl/SensorData.cpp
        CommandAndControl/SensorData.h
        CommandAndControl/CommandExecutor.cpp
        CommandAndControl/CommandExecutor.h)


# Link Lua library AFTER add_executable
target_link_libraries(GraduateProject lua)