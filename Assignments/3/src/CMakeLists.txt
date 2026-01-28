add_executable(game 
    Action.hpp
    Animation.hpp
    Assets.cpp
    Components.hpp
    Entity.hpp
    EntityManager.hpp
    GameEngine.cpp
    Physics.hpp
    Scene_Menu.cpp 
    Scene_Play.cpp 
    Scene.cpp
    Vec2.hpp
    main.cpp
    )
target_link_libraries(game PUBLIC ImGui-SFML::ImGui-SFML)
add_compile_definitions(ASSETS_PATH="${CMAKE_SOURCE_DIR}/bin/assets.txt")
add_custom_target(run
    COMMAND game
    DEPENDS game 
    )