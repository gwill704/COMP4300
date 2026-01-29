#include "Action.hpp"
#include "Assets.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <fstream>



class GameEngine
{
    std::map<std::string, std::shared_ptr<Scene>>            m_scenes;
    sf::RenderWindow                                         m_window;
    Assets&                                                  m_assets;
    std::string                                              m_currentScene;
    bool                                                     m_running;

    void init(const std::string& assetsFile);
    void update();
    void quit();
    
    template <typename T>
    void changeScene(GameEngine* game, const std::string& sceneName);

    Assets&             getAssets();
    sf::RenderWindow&   window();
    void                sUserInput();

public:
    GameEngine(const std::string& assetsFile);
    void run();
};