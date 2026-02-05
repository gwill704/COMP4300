#include "Action.hpp"
#include "Assets.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <fstream>
#include <memory>



class GameEngine
{
    std::map<std::string, std::shared_ptr<Scene>>            m_scenes;
    sf::RenderWindow                                         m_window;
    Assets&                                                  m_assets;
    std::string                                              m_currentScene;
    bool                                                     m_running;
    sf::Clock                                                m_deltaClock;

    void init(const std::string& assetsFile);
    void update();
    void quit();
    
    template <typename T, typename... TArgs>
    void changeScene(const std::string& sceneName, TArgs&&... args);
    Scene& currentScene();

    Assets&             getAssets();
    void                sUserInput();
    
    public:
    GameEngine(const std::string& assetsFile);
    void run();
    sf::RenderWindow&   window();
};