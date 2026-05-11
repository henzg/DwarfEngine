add_library(dwarf_engine
    src/Engine.cpp
    src/Registry.cpp
    src/Log.cpp
)

target_include_directories(dwarf_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
