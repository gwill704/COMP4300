#include "GameEngine.h"

void GameEngine::init(const std::string& config)
{
    
}


{
    std::map<const std::string&, Scene>     m_scenes;
    sf::Window                              m_window;
    Assets                                  m_assets;
    const std::string&                      m_scene;
    bool                                    m_running;

    void init(const std::string& config);
    void update();
    void quit();
    
    template <typename T>
    void changeScene();

    Assets& getAssets();
    sf::Window& window();
    void sUserInput();

public:
    GameEngine(const std::string& config);
    void run();
}