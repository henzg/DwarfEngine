cmake_policy(SET CMP0072 NEW)

cmake_minimum_required(VERSION 3.20)
project(Dwarf
            VERSION 1.0
            DESCRIPTION "Learning C++ by building a raw engine"
            LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Dwarf)
add_subdirectory(apps/project_aether)

