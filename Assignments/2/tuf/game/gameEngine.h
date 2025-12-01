#include <SFML/Graphics.hpp>

class Game 
{
    sf::RenderWindow m_window;
    EntityManager    m_entities;
    Entity           m_player;
    bool             m_paused;
    bool             m_running;
public:
    void init();
    void update();

    // Systems
    void sMovement();
    void sUserInput();
    void sRender();
    void sEnemySpawner();
    void sCollision();
};


class EntityManager
{
    std::vector<Entity> m_entities;
    std::map<std::string, Entity> m_entityMap;
    std::vector<Entity> m_toAdd;
public:
    void init();
    void update();
    sp<Entity>
};