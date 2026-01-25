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


template <typename T, typename... TArgs>
void GameEngine::changeScene(const std::string& sceneName, TArgs&&... args)
{
    if (m_scenes[sceneName])
    {
        m_currentScene = sceneName;
    }
    else
    {
        m_currentScene = sceneName;
        m_scenes[m_currentScene] = std::make_shared<T>(std::forward<TArgs>(args));
    }
}

Assets& getAssets()
{
    return m_assets.Instance();
}

//sf::RenderWindow& window()
{
    return m_window;
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
    
    //template <typename T, typename... TArgs>
    //void changeScene(const std::string& sceneName, TArgs&&... args);

    //Assets& getAssets();
    sf::RenderWindow& window();
    void sUserInput();

public:
    GameEngine(const std::string& config);
    void run();
}