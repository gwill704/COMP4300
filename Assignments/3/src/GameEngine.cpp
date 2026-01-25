#include "GameEngine.h"

void GameEngine::init()
{
    m_window.create(sf::VideoMode({1280, 720}), "Assignment 3");
    m_window.setFramerateLimit(60);
}

void GameEngine::update()
{
    m_scenes[m_currentScene]->update();
}

void GameEngine::quit()
{
    m_running = false;
}


template <typename T>
void changeScene()
{
    T newScene();
    m_currentScene = newScene.name();
    m_scenes[m_currentScene] = std::make_shared<T>();

}

{
    std::map<const std::string&, std::shared_ptr<Scene>>     m_scenes;
    sf::RenderWindow                                         m_window;
    Assets                                                   m_assets;
    const std::string&                                       m_currentScene;
    bool                                                     m_running;

    //void init();
    //void update();
    //void quit();
    
    template <typename T>
    void changeScene();

    Assets& getAssets();
    sf::RenderWindow& window();
    void sUserInput();

public:
    GameEngine(const std::string& config);
    void run();
}