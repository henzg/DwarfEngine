cmake_policy(SET CMP0072 NEW)

cmake_minimum_required(VERSION 3.20)
project(Dwarf
            VERSION 1.0
            DESCRIPTION "Learning C++ by building a raw engine"
            LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(DwarfEngine
        src/main.cpp
        src/Engine.cpp
        src/Registry.cpp
        src/Log.cpp
        src/Game.cpp)

target_include_directories(DwarfEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/include)

