add_executable(game main.cpp)
target_link_libraries(game PUBLIC ImGui-SFML::ImGui-SFML)
add_compile_definitions(ASSETS_PATH="${CMAKE_SOURCE_DIR}/") # now ASSETS_PATH is the source dir inside main.cpp
add_custom_target(run # ads make run command to accelerate evrisin
    COMMAND example
    DEPENDS example
    #WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )