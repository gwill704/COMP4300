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
    std::cout << "Window created" <<std::endl;
    m_window.setFramerateLimit(60);
    std::cout << "Window setFramerateLimit done" <<std::endl;

    // Read assetsFile
    getAssets().loadFromFile(assetsFile);
    std::cout << "Assets Loaded" <<std::endl;


    // Current scene
    m_running = true;
    std::string currentScene = "play";
    std::string levelPath = std::string(ASSETS_PATH) + "level1.txt";
    changeScene<Scene_Play>(currentScene, levelPath);
}

void GameEngine::update()
{
    std::cout << "GameEngine::update(): Pre-m_scenes[m_currentScene]->update()\n";
    if (m_scenes[m_currentScene]) std::cout << "update: m_scenes[m_currentScene] exists\n";
    m_scenes.at(m_currentScene)->update();
    /*
    if(m_scenes[m_currentScene])
    {
        m_scenes.at(m_currentScene)->update();
    }
    else
    {
        std::cout << "GameEngine::update(): no " << m_currentScene << "in m_scenes map\n";
    }
    */
}

void GameEngine::quit()
{
    m_running = false;
}


template <typename T, typename... TArgs>
void GameEngine::changeScene(const std::string& sceneName, TArgs&&... args)
{
    m_currentScene = sceneName;
    m_scenes.insert(std::make_pair(m_currentScene, std::make_shared<T>(*this, std::forward<TArgs>(args)...)));
}

Scene& GameEngine::currentScene()
{
    return *m_scenes.at(m_currentScene);
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
        std::cout << "running" << std::endl;
        std::cout << "GameEngine::run() pre-update()" << std::endl;
        update();
        m_window.display();
    }
}
