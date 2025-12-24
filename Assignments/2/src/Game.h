#pragma once

#include "Entity.h"
#include "EntityManager.h"

#include  <SFML/Graphics.hpp>

struct Color        { u_short R, G, B;                                                };
struct Wave         { float w, a;                                                      };
struct WindowConfig { int W,  H,  FL; bool FS;                                         };
struct FontConfig   { std::string F;    u_int S;              Color C;                   };
struct PlayerConfig { u_int SR, CR, OT, V;                  Color F, O;  float S;           };
struct EnemyConfig  { u_int SR, CR, OT, VMIN, VMAX, L, SI;  Color O;     float SMIN, SMAX;  };
struct BulletConfig { u_int SR, CR, OT, V, L;               Color F, O;  float S;           };

class Game
{
    sf::RenderWindow    m_window;           // the window we will draw to 
    EntityManager       m_entities;         // vector of entities to maintain
    sf::Font            m_font;             // the font we will use to draw
    sf::Text            m_text;             // the score text to be drawn to the screen 
    sf::Text            m_cooldown_text;
    WindowConfig        m_windowConfig;  
    FontConfig          m_fontConfig;   
    PlayerConfig        m_playerConfig;
    EnemyConfig         m_enemyConfig;
    BulletConfig        m_bulletConfig;
    int                 m_score = 0;
    int                 m_currentFrame = 0;
    int                 m_lastEnemySpawnTime = 0;
    int                 m_nuclear_cooldown = 0;
    u_int               m_nuclear_cooldown_interval = 60;
    Wave                m_waves;
    u_int               m_nuclear_gen_max = 5;
    float               m_nuclear_angle = M_PI / 11;
    int                 m_nuclear_speed = 5;
    bool                m_paused = false;   // whether we update game logic
    bool                m_running = true;   // whether the game is running

    std::shared_ptr<Entity> m_player;

    void init(const std::string & config);  // initialize the GameState with a config file path
    void setPaused(bool paused);            // pause the game

    void sMovement();                       // System: Entity position / movement update
    void sUserInput();                      // System: User input
    void sLifespan();                       // System: Lifespan
    void sRender();                         // System: Render / Drawing
    void sEnemySpawner();                   // System: Spawns Enemies
    void sCollision();                      // System: Collisions
    void sSpecialWeaponCooldown();          // System: Special Weapon Cooldown


    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2 & target);

public:

    Game(const std::string & config);  // constructor, takes in game config

    void run();
};