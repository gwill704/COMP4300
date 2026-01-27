add_executable(game main.cpp)
target_link_libraries(game PUBLIC ImGui-SFML::ImGui-SFML)
add_compile_definitions(ASSETS_PATH="${CMAKE_SOURCE_DIR}/bin/assets.txt")
add_custom_target(run
    COMMAND game
    DEPENDS game 
    )