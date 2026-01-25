#pragma once

#include "Action.hpp"
#include "Assets.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <fstream>


class GameEngine
{
    std::map<const std::string&, std::shared_ptr<Scene>>     m_scenes;
    sf::RenderWindow                                         m_window;
    Assets                                                   m_assets;
    const std::string&                                       m_currentScene;
    bool                                                     m_running;

    void init(const std::string& config);
    void update();
    void quit();
    
    template <typename T>
    void changeScene();

    Assets& getAssets();
    sf::RenderWindow& window();
    void sUserInput();

public:
    GameEngine(const std::string& config);
    void run();
}