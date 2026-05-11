add_executable(ProjectAether
    main.cpp
    Game.cpp
)

target_include_directories(ProjectAether
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ProjectAether
    PRIVATE
        dwarf_engine
)
