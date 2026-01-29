#include "GameEngine.h"
#include "Scene_Menu.h"
#include "Scene_Play.h"



GameEngine::GameEngine(const std::string& assetsFile)
    : m_assets(getAssets())
{
    init(assetsFile); 
}


void GameEngine::init(const std::string& assetsFile)
{
    m_window.create(sf::VideoMode({1280, 720}), "Assignment 3");
    m_window.setFramerateLimit(60);

    // Read assetsFile
    getAssets().loadFromFile(assetsFile);

    // Current scene
    std::string currentScene = "play";
    changeScene<Scene_Play>(this, currentScene);
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
void GameEngine::changeScene( GameEngine* game, const std::string& sceneName)
{
    if (m_scenes.find(sceneName) != m_scenes.end())
    {
        m_currentScene = sceneName;
    }
    else
    {
        m_currentScene = sceneName;
        m_scenes[m_currentScene] = std::make_shared<T>(this, sceneName);
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
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                window().close();
            }
        }
    }
}

void GameEngine::run()
{
    while(m_running)
    {
        update();
    }
}
