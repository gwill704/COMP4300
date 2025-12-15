#include "Game.h"

#include <iostream>
#include <fstream>
#include <math.h>

Game::Game(const std::string & config)
{
    init(config);
}

void Game::init(const std::string & config)
{
    // TODO: read in config file here
    //       use the premade PlayerConfig, EnemyConfig, BulletConfig variables

    std::string path = "../bin/config.txt";
    std::string instruction;


    std::ifstream fin(path);
    if (!fin.is_open())
        {
            std::cerr << "ERROR: Default constructor Config() tried to read config.txt, and" 
                      << " maybe it doesn't exist" << std::endl;
            exit(-1);
        }
    
    fin >> instruction >> m_windowConfig.W   >> m_windowConfig.H   >> m_windowConfig.FL  >> m_windowConfig.FS; 
    fin >> instruction >> m_fontConfig.F     >> m_fontConfig.S     >> m_fontConfig.C.R   >> m_fontConfig.C.G   >> m_fontConfig.C.B;
    fin >> instruction >> m_playerConfig.SR  >> m_playerConfig.CR  >> m_playerConfig.S   >> m_playerConfig.F.R >> m_playerConfig.F.G >> m_playerConfig.F.B
                       >> m_playerConfig.O.R >> m_playerConfig.O.G >> m_playerConfig.O.B >> m_playerConfig.OT  >> m_playerConfig.V;
    fin >> instruction >> m_enemyConfig.SR   >> m_enemyConfig.CR   >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX
                       >> m_enemyConfig.O.R  >> m_enemyConfig.O.G  >> m_enemyConfig.O.B  >> m_enemyConfig.OT   >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
                       >> m_enemyConfig.L    >> m_enemyConfig.SI;
    fin >> instruction >> m_bulletConfig.SR  >> m_bulletConfig.CR  >> m_bulletConfig.S   >> m_bulletConfig.F.R >> m_bulletConfig.F.G >> m_bulletConfig.F.B
                       >> m_bulletConfig.O.R >> m_bulletConfig.O.G >> m_bulletConfig.O.B >> m_bulletConfig.OT  >> m_bulletConfig.V   >> m_bulletConfig.L;
    
    // set up default window parameters
    if (!m_windowConfig.FS) m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Assignment 2");
    else                    m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Assignment 2", sf::Style::Fullscreen);

    m_window.setFramerateLimit(m_windowConfig.FL);

    srand(time(NULL));

    spawnPlayer();
    spawnEnemy();
    
}

void Game::run()
{
    // TODO: add pause functionality in here
    //       some systems should function while paueed (rendering)
    //       soem systems should't (movement / input)
    while (m_running)
    {

        m_entities.update();

       // if (!m_paused)
       // {
            sEnemySpawner();
            sMovement();
            sCollision();
            sUserInput();
       // }

        
        sRender();


        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }
}

void Game::setPaused (bool paused)
{
    // TODO
}

    // respawn the player in the middle of the screen 
void Game::spawnPlayer()
{
    // TODO: Finish adding all properties of the player with the correct values from the config

    // We create every entity by calling EntityManager.addEntity(tag)
    // Thisreturns a std::shared_ptr<Entity>, so we use 'auto' to save typing
    auto entity = m_entities.addEntity("player");

    // Give this entity a Transform so it spawns at (200, 200) with velocity (1, 1) and angle 0
    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(0.0f, 0.0f), 0);

    // The entity's shape will have radius 32, 8 sides, dark grey fill, and red outline of thickness 4
    entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, 
                                              sf::Color(m_playerConfig.F.R, m_playerConfig.F.G, m_playerConfig.F.B), 
                                              sf::Color(m_playerConfig.O.R, m_playerConfig.O.G, m_playerConfig.O.B),
                                              m_playerConfig.OT);

    // Add an input component to the player so that we can use inputs
    entity->cInput = std::make_shared<CInput>();

    // Since we want this Entity to be our player, set our Game's player variable to be this Entity
    // This goes slightly against the EntityManager paradigm, but we use the player so much it's worth it
    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //       the enemy must be spawned completely within the bounds of the window
    //

    auto entity = m_entities.addEntity("enemy");

    // Give this entity a Transform so it spawns at (200, 200) with velocity (1, 1) and angle 0
    float ex = (rand() % ((m_window.getSize().x - m_enemyConfig.SR) - 2 * m_playerConfig.SR + 1)) + 2 * m_playerConfig.SR;
    float ey = (rand() % ((m_window.getSize().y - m_enemyConfig.SR) - 2 * m_playerConfig.SR + 1)) + 2 * m_playerConfig.SR;

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(1.0f, 1.0f), 0.0f);

    // The entity's shape will have radius 32, 8 sides, dark grey fill, and red outline of thickness 4
    Color ec = {static_cast<u_short>(rand() % 255),
                static_cast<u_short>(rand() % 255),
                static_cast<u_short>(rand() % 255)};

    float ev = m_enemyConfig.VMIN + (rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));

    entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, ev, sf::Color(ec.R, ec.G, ec.B), 
                                              sf::Color(m_enemyConfig.O.R, m_enemyConfig.O.G, m_enemyConfig.O.B),
                                              m_enemyConfig.OT);

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

// spawns the small enemies when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO: spawn small enemies at the location of the input enemy e

    // when we create the smaller enemy, we have to read the values of the original enemy
    // - spawn a number of small enemies equal to the vertices of the original enemy
    // - set each small enemy to the same color as the original, half the size
    // - small enemies are worth double points of the original enemy
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target)
{
    // TODO: implement the spawning of a bullet which travels toward target
    //.      - bullet speed is given as a scalar speed
    //.      - you must set the velocity by using formula in notes
    auto bullet = m_entities.addEntity("bullet");

    auto tpos   = entity->cTransform->pos.dist(target).normalize();
    std::cout << "tpos = " << tpos.y << std::endl;
    
    

    bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos + tpos * m_playerConfig.SR, 
                                                      tpos * m_bulletConfig.S, 
                                                      0.0f);
    
    bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V,
                                              sf::Color(m_bulletConfig.F.R, m_bulletConfig.F.G, m_bulletConfig.F.B), 
                                              sf::Color(m_bulletConfig.O.R, m_bulletConfig.O.G, m_bulletConfig.O.B), m_bulletConfig.OT);
}


void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO: implement your own special weapon
}

void Game::sMovement()
{
    // TODO: implement all entity movement in this function
    //.       you should read the m_player->cInput component to determine if the player is moving
    
    
    m_player->cTransform->velocity = Vec2(0.0f, 0.0f);
    if (m_player->cInput->up)     m_player->cTransform->velocity += Vec2( 0.0f, -1.0f);
    if (m_player->cInput->down)   m_player->cTransform->velocity += Vec2( 0.0f,  1.0f);
    if (m_player->cInput->left)   m_player->cTransform->velocity += Vec2(-1.0f,  0.0f);
    if (m_player->cInput->right)  m_player->cTransform->velocity += Vec2( 1.0f,  0.0f);

    m_player->cTransform->velocity.normalize();
    m_player->cTransform->velocity *= m_playerConfig.S;

    // Sample movement speed update
    for (auto e : m_entities.getEntities())
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
}

void Game::sLifespan()
{
    // TODO: implement all lifespan functionality

    // for all entities
    //      if entity has no lifespan component, skip it
    //      if entity has > 0 remaining lifespan, substract 1
    //      if it has lifespan and is alive
    //.         scale its alpha channel properly
    //      if it has lifespan and its time is up
    //          destroy the entity
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities
    //        be sure to use the collision radius, NOT the shape radius
}

void Game::sEnemySpawner()
{
    // TODO: code which implements enemy spawning should go here
    //          
    //          (use m_currentFrame - m_lastEnemySpawnTime) to determine
    //          how long it has been since the last enemy spawned

}

void Game::sRender()
{
    // TODO: change the code below to draw ALL of the entities
    //.      sample drawing of the player Entity that we have created
    m_window.clear();

    // draw all the entity's sf::CircleShape   
    for (auto e : m_entities.getEntities())
    {
        //std::cout << "New entity: " << e->id() << std::endl;
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);

        m_window.draw(e->cShape->circle);
    }

    m_window.display();
}

void Game::sUserInput()
{
    // TODO: handle user input here
    //       note that you should only be setting the player's input component variables here
    //       you should not implement the player's movement logic here
    //       the movement system will read the variables you set in this function

    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // this event triggers when the window is closed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W Key Pressed\n";
                // TODO: set player's input component "up" to true
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::A:
                std::cout << "A Key Pressed\n";
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::D:
                std::cout << "D Key Pressed\n";
                m_player->cInput->right = true;
                break;
            case sf::Keyboard::S:
                std::cout << "S Key Pressed\n";
                m_player->cInput->down = true;
                break;
            default: break;
            }
        }

        // this event is triggered when a key is released
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W Key Released\n";
                // TODO: set player's input component "up" to true
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::A:
                std::cout << "A Key Released\n";
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::D:
                std::cout << "D Key Released\n";
                m_player->cInput->right = false;
                break;
            case sf::Keyboard::S:
                std::cout << "S Key Released\n";
                m_player->cInput->down = false;
                break;
            default: break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Left Mouse Button Clicked at {" << event.mouseButton.x << ", " << event.mouseButton.y << "}\n";
                // call spawnBullet here
                spawnBullet(m_player, m_entities.getEntities("enemy")[0]->cTransform->pos);

            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "Right Mouse Button Clicked at {" << event.mouseButton.x << ", " << event.mouseButton.y << "}\n";
                // call spawnSpecialWeapon here
            }
        }
    }
}