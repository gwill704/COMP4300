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
    m_window.create(sf::VideoMode({1280, 920}), "Assignment 3");
    m_window.setFramerateLimit(60);

    // Read assetsFile
    getAssets().loadFromFile(assetsFile);

     // initialize imgui
    if (!ImGui::SFML::Init(m_window))
    {
        std::cerr << "ERROR: Could not load the window in ImGui\n";
        std::exit(-1);
    }

    // scale the imgui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.f;


    // Current scene
    m_running = true;
    std::string currentScene = "play";
    std::string levelPath = std::string(ASSETS_PATH) + "level1.txt";
    changeScene<Scene_Play>(currentScene, levelPath);
}

void GameEngine::update()
{
    ImGui::SFML::Update(m_window, m_deltaClock.restart());
    if (m_scenes[m_currentScene])
    {
        m_scenes.at(m_currentScene)->update();
    }
    else 
    {
        std::cerr << "ERROR: GameEngine::update(): m_scenes.at[m_currentScene] does not exist for m_currentScene = " << m_currentScene << std::endl;
        exit(-1);
    }
    ImGui::SFML::Render(m_window);
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
        ImGui::SFML::ProcessEvent(m_window, *event);
        if (event->is<sf::Event::Closed>())
        {
            quit();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                quit();
            }
        }
    }
}

void GameEngine::run()
{
    while(m_running)
    {
        update();
        m_window.display();
        sUserInput();
    }
    ImGui::SFML::Shutdown();
}
