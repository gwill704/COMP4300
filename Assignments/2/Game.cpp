#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game(const std::string & config)
{
    init(config);
}

void Game::init(const std::string & config)
{
    // TODO: read in config file here
    //.      use the premade PlayerConfig, EnemyConfig, BulletConfig variables

    std::ifstream fin(path);

    fin >> m_playerConfig.SR >> m_playerConfig.CR; 

    // set up default window parameters
    m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
    m_window.setFramerateLimit(60);

    spawnPlayer();

}

void Game::run()
{
    // TODO: add pause functionality in here
    //       some systems should function while paueed (rendering)
    //       soem systems should't (movement / input)
    while (m_running)
    {

        m_entities.update();

        if (!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
            sUserInput();
        }

        
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
    auto enitity = m_entities.addEntity("player");
    
}