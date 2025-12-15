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
        lua_driver.cpp)


# Link Lua library AFTER add_executable
target_link_libraries(GraduateProject lua)