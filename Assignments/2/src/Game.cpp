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
    fin >> instruction >> m_waves.w >> m_waves.a;
    
    // set up default window parameters
    if (!m_windowConfig.FS) m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Assignment 2");
    else                    m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Assignment 2", sf::Style::Fullscreen);

    m_window.setFramerateLimit(m_windowConfig.FL);

    srand(time(NULL));

    if(!m_font.loadFromFile(m_fontConfig.F)) std::cerr << "No font file provided\n";
    m_text.setFont(m_font);
    m_text.setCharacterSize(m_fontConfig.S);
    m_text.setColor(sf::Color(m_fontConfig.C.R, m_fontConfig.C.G, m_fontConfig.C.B, 255));
    m_text.setPosition(0.0f, 0.0f);

    m_cooldown_text.setFont(m_font);
    m_cooldown_text.setCharacterSize(m_fontConfig.S);
    m_cooldown_text.setColor(sf::Color(0,255,0,255));
    m_cooldown_text.setPosition(m_window.getSize().x * 0.8, 0.0f);

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

        if (!m_player->isActive()) spawnPlayer();

        if (!m_paused)
        {
            sEnemySpawner();
            sSpecialWeaponCooldown();
            sMovement();
            sCollision();
            sLifespan();
        }

        sUserInput();
        
        sRender();


        // increment the current frame
        // may need to be moved when pause implemented
        m_currentFrame++;
    }
}

void Game::setPaused (bool paused)
{
    // TODO
    m_paused = paused;
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

    entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

    entity->cNuclearRadiation = std::make_shared<CNuclearRadiation>(0);

    m_nuclear_cooldown = m_currentFrame;

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

    Vec2  es (rand(), rand());
    es.normalize();

    float s = (((float) rand()) / (float) RAND_MAX) * (m_enemyConfig.SMAX - m_enemyConfig.SMIN) + m_enemyConfig.SMIN; 

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), es * s, 0.0f);

    // The entity's shape will have radius 32, 8 sides, dark grey fill, and red outline of thickness 4
    Color ec = {static_cast<u_short>(rand() % 255),
                static_cast<u_short>(rand() % 255),
                static_cast<u_short>(rand() % 255)};

    int ev = m_enemyConfig.VMIN + (rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));

    entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, ev, sf::Color(ec.R, ec.G, ec.B), 
                                              sf::Color(m_enemyConfig.O.R, m_enemyConfig.O.G, m_enemyConfig.O.B),
                                              m_enemyConfig.OT);

    
                                            
    entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

    entity->cScore = std::make_shared<CScore>(100 * ev);

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

    if (e->cLifespan) return;
    float d_angle = 2 * M_PI /(float) e->cShape->circle.getPointCount();
    for (float angle = 0; angle < 2 * M_PI; angle += d_angle)
    {
        auto se = m_entities.addEntity("enemy");
        se->cTransform = std::make_shared<CTransform>(e->cTransform->pos, Vec2(angle) * e->cTransform->velocity.length(), 0.0f);
        se->cShape     = std::make_shared<CShape>(m_enemyConfig.SR * 0.5, e->cShape->circle.getPointCount(), e->cShape->circle.getFillColor(),
                                                  e->cShape->circle.getOutlineColor(), e->cShape->circle.getOutlineThickness());
        se->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR * 0.5);
        se->cLifespan  = std::make_shared<CLifespan>(m_enemyConfig.L);
        se->cScore = std::make_shared<CScore>(e->cScore->score * 2);
    }
}

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target)
{
    // TODO: implement the spawning of a bullet which travels toward target
    //.      - bullet speed is given as a scalar speed
    //.      - you must set the velocity by using formula in notes
    auto bullet = m_entities.addEntity("bullet");

    auto tpos   = entity->cTransform->pos.dist(target).normalize();

    bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos + tpos * m_playerConfig.SR, 
                                                      tpos * m_bulletConfig.S, 
                                                      0.0f);
    
    bullet->cShape     = std::make_shared<CShape>     (m_bulletConfig.SR, m_bulletConfig.V,
                                                      sf::Color(m_bulletConfig.F.R, m_bulletConfig.F.G, m_bulletConfig.F.B), 
                                                      sf::Color(m_bulletConfig.O.R, m_bulletConfig.O.G, m_bulletConfig.O.B), m_bulletConfig.OT);

    bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);

    bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
}


void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2 & target)
{
    // TODO: implement your own special weapon
    if (entity->cNuclearRadiation->m_nuclear_gen_counter != 0)
    {
        auto bullet = m_entities.addEntity("bullet");
        
        auto tpos   = entity->cTransform->pos.dist(target).normalize();

        bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos + tpos * m_playerConfig.SR, 
                                                         tpos * m_nuclear_speed * pow(1.3, (m_nuclear_gen_max - entity->cNuclearRadiation->m_nuclear_gen_counter)), 
                                                         0.0f);
        
        float radius = entity->cShape->circle.getLocalBounds().width;

        bullet->cShape     = std::make_shared<CShape>   (radius * 0.35, entity->cNuclearRadiation->m_nuclear_gen_counter + 2,
                                                        sf::Color(m_bulletConfig.F.R, m_bulletConfig.F.G, m_bulletConfig.F.B), 
                                                        sf::Color(m_bulletConfig.O.R, m_bulletConfig.O.G, m_bulletConfig.O.B), m_bulletConfig.OT);

        bullet->cCollision = std::make_shared<CCollision>(radius * 0.35);

        bullet->cNuclearRadiation = std::make_shared<CNuclearRadiation>(entity->cNuclearRadiation->m_nuclear_gen_counter);

        if (entity->tag() == "player") entity->cNuclearRadiation->m_nuclear_gen_counter--;
    }
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

    for (auto e : m_entities.getEntities())
    {
        if (!e->cLifespan)
        {
            continue;
        }

        if (e->cLifespan->remaining > 0)
        {
            e->cLifespan->remaining--;
        }

        if (e->cLifespan && e->isActive())
        {
            const sf::Color & e_fillcolor = e->cShape->circle.getFillColor();
            const sf::Color & e_outcolor  = e->cShape->circle.getOutlineColor();
            float alpha = ( (float) e->cLifespan->remaining / (float) e->cLifespan->total )  * 255;
            e->cShape->circle.setFillColor(sf::Color(e_fillcolor.r, e_fillcolor.g, e_fillcolor.b, alpha));
            e->cShape->circle.setOutlineColor(sf::Color(e_outcolor.r, e_outcolor.g, e_outcolor.b, alpha));
        }

        if (e->cLifespan && e->cLifespan->remaining == 0)
        {
            e->destroy();
        }
    }
}

void Game::sCollision()
{
    // TODO: implement all proper collisions between entities 
    //        be sure to use the collision radius, NOT the shape radius

    Vec2 & player_pos = m_player->cTransform->pos;
    float & player_col = m_player->cCollision->radius;

    if ((player_pos.x + player_col) > m_window.getSize().x)   m_player->cTransform->pos.x += m_window.getSize().x - (player_pos.x + player_col);
    if ((player_pos.x - player_col) < 0.0)                    m_player->cTransform->pos.x -= player_pos.x - player_col;
    if ((player_pos.y + player_col) > m_window.getSize().y)   m_player->cTransform->pos.y += m_window.getSize().y - (player_pos.y + player_col);
    if ((player_pos.y - player_col) < 0.0)                    m_player->cTransform->pos.y -= player_pos.y - player_col; 

    for (auto e : m_entities.getEntities("enemy"))
    {
        if (!e->isActive()) continue;
        Vec2 & e_pos = e->cTransform->pos;
        float & e_col = e->cCollision->radius;

        if ((e_pos.x + e_col) > m_window.getSize().x)
            {
                e->cTransform->pos.x += m_window.getSize().x - (e_pos.x + e_col);
                e->cTransform->velocity.x *= -1;
            }
            if ((e_pos.x - e_col) < 0.0)
            {
                e->cTransform->pos.x -= e_pos.x - e_col;
                e->cTransform->velocity.x *= -1;
            }

            if ((e_pos.y + e_col) > m_window.getSize().y)
            {
                e->cTransform->pos.y += m_window.getSize().y - (e_pos.y + e_col);
                e->cTransform->velocity.y *= -1;
            }
            if ((e_pos.y - e_col) < 0.0)
            {
                e->cTransform->pos.y -= e_pos.y - e_col; 
                e->cTransform->velocity.y *= -1;
            }


        if (e_pos.dist(player_pos).length2() < (e_col + player_col) * (e_col + player_col))
        {
            m_player->destroy();
            spawnSmallEnemies(e);
            e       ->destroy();
            m_score = 0;
        }

        for (auto bullet : m_entities.getEntities("bullet"))
        {
            if (!bullet->isActive()) continue;

            Vec2  & bullet_pos = bullet->cTransform->pos;
            float & bullet_col = bullet->cCollision->radius;

            if (bullet_pos.dist(e_pos).length2() < (bullet_col + e_col) * (bullet_col + e_col))
            {
                if (!bullet->cNuclearRadiation)
                {
                    spawnSmallEnemies(e);
                    e->destroy();
                    m_score += e->cScore->score;
                    bullet->destroy();
                } 

                if (bullet->cNuclearRadiation)
                {
                    float initial_angle = bullet->cTransform->velocity.getAngle();
                    Vec2 sb1 (cosf(initial_angle + m_nuclear_angle), -sinf(initial_angle + m_nuclear_angle));
                    Vec2 sb2 (cosf(initial_angle - m_nuclear_angle), -sinf(initial_angle - m_nuclear_angle));

                    sb1 = bullet->cTransform->pos + sb1;
                    sb2 = bullet->cTransform->pos + sb2;
                    
                    bullet->cNuclearRadiation->m_nuclear_gen_counter--;
                    spawnSmallEnemies(e);
                    e->destroy();
                    spawnSpecialWeapon(bullet, sb1);
                    spawnSpecialWeapon(bullet, sb2);
                    bullet->destroy();
                    m_score += e->cScore->score;
                } 
            }
        }
    }

    for (auto bullet : m_entities.getEntities("bullet"))
    {
        if (!bullet->isActive()) continue;
        if (bullet->cNuclearRadiation)
        {
            Vec2 &  bullet_pos = bullet->cTransform->pos;
            float & bullet_col = bullet->cCollision->radius;

            if ((bullet_pos.x + bullet_col) > m_window.getSize().x)
            {
                bullet->cTransform->pos.x += m_window.getSize().x - (bullet_pos.x + bullet_col);
                bullet->cTransform->velocity.x *= -1;
            }
            if ((bullet_pos.x - bullet_col) < 0.0)
            {
                bullet->cTransform->pos.x -= bullet_pos.x - bullet_col;
                bullet->cTransform->velocity.x *= -1;
            }

            if ((bullet_pos.y + bullet_col) > m_window.getSize().y)
            {
                bullet->cTransform->pos.y += m_window.getSize().y - (bullet_pos.y + bullet_col);
                bullet->cTransform->velocity.y *= -1;
            }
            if ((bullet_pos.y - bullet_col) < 0.0)
            {
                bullet->cTransform->pos.y -= bullet_pos.y - bullet_col; 
                bullet->cTransform->velocity.y *= -1;
            }
        }
    }
}

void Game::sEnemySpawner()
{
    // TODO: code which implements enemy spawning should go here
    //          
    //          (use m_currentFrame - m_lastEnemySpawnTime) to determine
    //          how long it has been since the last enemy spawned
    if ((m_currentFrame - m_lastEnemySpawnTime) / m_enemyConfig.SI == 1)
    {
        spawnEnemy();
    }
}

void Game::sSpecialWeaponCooldown()
{
    if (((m_currentFrame - m_nuclear_cooldown) / m_nuclear_cooldown_interval == 1) && m_player->cNuclearRadiation->m_nuclear_gen_counter < m_nuclear_gen_max)
    {
        m_player->cNuclearRadiation->m_nuclear_gen_counter++;
        m_nuclear_cooldown = m_currentFrame;
    }
}

void Game::sRender()
{
    // TODO: change the code below to draw ALL of the entities
    //.      sample drawing of the player Entity that we have created
    m_window.clear();

    // draw all the entity's sf::CircleShape   
    for (auto e : m_entities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        e->cShape->circle.setScale(1 + cosf(e->cTransform->angle * m_waves.w) * m_waves.a, 1 + cosf(e->cTransform->angle * m_waves.w) * m_waves.a);

        if (e->tag() == "bullet" && e->cNuclearRadiation)
        {
            e->cShape->circle.setFillColor(sf::Color(0, 
                                                     abs(cosf(e->cTransform->angle * m_waves.w)) * 255,
                                                     0, 255));
        }

        m_window.draw(e->cShape->circle);
    }

    // draw score
    m_text.setString((std::string) "SCORE " + std::to_string(m_score));
    m_window.draw(m_text);

    m_cooldown_text.setString((std::string) "NUCLEAR POWER " + std::to_string(m_player->cNuclearRadiation->m_nuclear_gen_counter));
    m_window.draw(m_cooldown_text);    

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
                // TODO: set player's input component "up" to true
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = true;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = true;
                break;

            case sf::Keyboard::P:
                if(m_paused) setPaused(false);
                else         setPaused(true);
            default: break;
            }
        }

        // this event is triggered when a key is released
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                // TODO: set player's input component "up" to true
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = false;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = false;
                break;

            case sf::Keyboard::Escape:
                m_running = false;
            default: break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                Vec2 mouse_pos (event.mouseButton.x, event.mouseButton.y);
                if (!m_paused) spawnBullet(m_player, mouse_pos);
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                // call spawnSpecialWeapon here
                Vec2 mouse_pos (event.mouseButton.x, event.mouseButton.y);
                spawnSpecialWeapon(m_player, mouse_pos);
            }
        }
    }
}