target_sources(${PROJECT_NAME}
    PRIVATE Main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Basic)
add_subdirectory(Window)
add_subdirectory(Utility)

# add_subdirectory(Global)

