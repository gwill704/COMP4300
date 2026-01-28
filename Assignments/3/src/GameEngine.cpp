#include "GameEngine.h"



GameEngine::GameEngine(const std::string& assetsFile)
    : m_assets(getAssets()), m_currentScene("menu")
{
    init(assetsFile); 
}


void GameEngine::init(const std::string& assetsFile)
{
    m_window.create(sf::VideoMode({1280, 720}), "Assignment 3");
    m_window.setFramerateLimit(60);

    // Read assetsFile
    getAssets().loadFromFile(assetsFile);
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
    if (m_scenes.find(sceneName) != m_scenes.end())
    {
        m_currentScene = sceneName;
    }
    else
    {
        m_currentScene = sceneName;
        m_scenes[m_currentScene] = std::make_shared<T>(std::forward<TArgs>(args)...);
    }
}

Assets& GameEngine::getAssets()
{
    return m_assets.Instance();
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}

void GameEngine::sUserInput() ///// TODODODODODO
{
    while (auto event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::KeyBoard::Scancode::Escape)
            {
                window().close();
            }
        }
    }
}

void GameEngine::run()
{
    changeScene<Scene_Play>("Play")
    while(m_running)
    {
        m_scenes[m_currentScene]->loadLevel
    }
}
