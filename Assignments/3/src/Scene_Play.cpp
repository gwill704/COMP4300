#include "Scene_Play.h"
#include "Physics.hpp"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.hpp"
#include "Action.hpp"

Scene_Play::Scene_Play(GameEngine& gameEngine, const std::string& levelPath)
    : Scene(gameEngine)
    , m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::Scancode::P,       "PAUSE");
    registerAction(sf::Keyboard::Scancode::Escape,  "QUIT");
    registerAction(sf::Keyboard::Scancode::T,       "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::Scancode::C,       "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::Scancode::G,       "TOGGLE_GRID");

    // Player movement
    registerAction(sf::Keyboard::Scancode::A,       "GO_LEFT");
    registerAction(sf::Keyboard::Scancode::D,       "GO_RIGHT");
    registerAction(sf::Keyboard::Scancode::W,       "GO_UP");
    registerAction(sf::Keyboard::Scancode::S,       "GO_DOWN");
    registerAction(sf::Keyboard::Scancode::Space,   "SHOOT");

    // TODO: Register all other gameplay Actions

    loadLevel(levelPath);
}

Vec2f Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    // TODO:: This function takes in a grid (x, y) position and an Entity
    //        Return a Vec2 indicating where the CENTER position of the Entity should be
    //        You must use the Entity Animation size to position it correctly 
    //              entity->get<CAnimation>().getSize()
    //        The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
    //        The bottom-left corner of Animation should align with the bottom left of the grid
    //
    //        Remember that SFML has (0,0) int hte top left, while grid coordinates are specified in the bottom left.
    //        You cna get the size of the sfml window via m_game.window()..getSize();
    Vec2f actualPosition( gridX * m_gridSize.x + entity->get<CAnimation>().animation.getSize().x / 2,
                          m_game.window().getSize().y - (gridY * m_gridSize.y + entity->get<CAnimation>().animation.getSize().y / 2));

    return actualPosition;
}

void Scene_Play::loadLevel(const std::string& levelPath)
{
    // reset the entity mangaer every time we load a level 
    m_entityManager = EntityManager();

    // TODO : read in the level file and add the appropiae entities
    //       use the PlayerConfig struct m_playerConfig to store player properties
    //       this struct is defined at the top of Scene_Play.h

    // Note: all of the code below is a sample code which shows you how to 
    //       set up and use entities it should be removed

    std::ifstream fin(levelPath);
    if (!fin.is_open())
    {
      std::cerr << "ERROR: Scene_Play: Input file of levelPath '" << levelPath << "' does not exist" << std::endl;
    }

    std::string instruction;
    std::string name;
    int x, y;
    while (fin >> instruction) 
    {
      if (instruction == "Tile")
      {
        auto tile = m_entityManager.addEntity("tile");
        fin >> name >> x >> y;
        tile->add<CAnimation>(Assets::Instance().getAnimation(name), true);
        if (name == "Question")
        {
          tile->add<CState>("noHit");
        }
        tile->add<CTransform>(gridToMidPixel(x, y, tile));
        tile->add<CBoundingBox>( Assets::Instance().getAnimation(name).getSize() ); 
        // tiles' position is static and equal to current position
        // To do that more general and if there were tiles that move, this should be implemented in sMovement
        tile->get<CTransform>().prevPos = tile->get<CTransform>().pos;
      }
      if (instruction == "Dec")
      {
        auto decoration = m_entityManager.addEntity("dec");
        fin >> name >> x >> y;
        decoration->add<CAnimation>(Assets::Instance().getAnimation(name), true);
        decoration->add<CTransform>(gridToMidPixel(x, y, decoration));
        // decorations' position is static and equal to current position
        decoration->get<CTransform>().prevPos = decoration->get<CTransform>().pos;
      }
      if (instruction == "Player")
      {
        fin >> m_playerConfig.X >> m_playerConfig.Y >> m_playerConfig.CX >> m_playerConfig.CY;
        fin >> m_playerConfig.SPEED >> m_playerConfig.JUMP >> m_playerConfig.MAXSPEED;
        fin >> m_playerConfig.GRAVITY;
        fin >> m_playerConfig.WEAPON;
      }
    }
    

    spawnPlayer();



/*
    auto block = m_entityManager.addEntity("tile");
    block->add<CAnimation>(Assets::Instance().getAnimation("Block"), true);
    block->add<CTransform>(gridToMidPixel(1,1, block));
    // add a bounding box, this will now show up if we press the 'C' key
    block->add<CBoundingBox>(Vec2f(block->get<CAnimation>().animation.getSize().x,
                                   block->get<CAnimation>().animation.getSize().y));

    // some sample entities
    auto brick = m_entityManager.addEntity("tile");
    // IMPORTANT: always add the CAnimation component first so that gridToMidPixel can compile
    brick->add<CAnimation>(Assets::Instance().getAnimation("Brick"), true);
    brick->add<CTransform>(Vec2f(96,480));
    // NOTE: You final code should position the entity with the grid x, y, position read from the level File
    // brick->add<CTransform>(gridToMidPixel(gridX, gridY, brick));

    if (brick->get<CAnimation>().animation.getName() == "Brick")
    {
        // This could be a good way of identifying if a tile is a brick!
    }

    auto block = m_entityManager.addEntity("tile");
    block->add<CAnimation>(Assets::Instance().getAnimation("Block"), true);
    block->add<CTransform>(Vec2f(224, 480));
    // add a bounding box, this will now show up if we press the 'C' key
    block->add<CBoundingBox>(Vec2f(block->get<CAnimation>().animation.getSize().x,
                                   block->get<CAnimation>().animation.getSize().y));

    auto question = m_entityManager.addEntity("tile");
    question->add<CAnimation>(Assets::Instance().getAnimation("Question"), true);
    question->add<CTransform>(Vec2f (352, 480));

    // NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
    //       Components are now returned as references rather than pointers
    //       If you do not specify a reference variable type, it will COPY the component
    //       Here is an example:
    //
    //       This will COPY the transform into the variable 'transform1' - it is INCORRECT
    //       Any changes you make to transform1 won't change inside the entity
    //       auto transform1 = entity->get<CTransform>()
    //
    //       This will REFERENCE the transform with the variable 'transform2' - it is CORRECT 
    //       Now any changes you make to transform2 will be changed inside the entity
  */  //       auto& transform2 = entity->get<CTransform>()
}

void Scene_Play::spawnPlayer()
{
    // check to see if a player already exists before adding a new one 
    // if it already exists, just overwrite the values of the existing one
    if (!m_player) { m_player = m_entityManager.addEntity("player"); }

    // here is a sample player entity which you can use to construct other entities
    m_player->add<CAnimation>(Assets::Instance().getAnimation("Stand"), true);
    m_player->add<CTransform>(gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player));
    m_player->add<CBoundingBox>(Vec2f(m_playerConfig.CX, m_playerConfig.CY));
    m_player->add<CState>("stand");
    m_player->add<CInput>();
    m_player->add<CGravity>(m_playerConfig.GRAVITY);

    // TODO: be sure to add the remaining components to the player
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
    // TODO: this should spawn a bullet at the given entity, 
    //       going in the direction the entity is facing 
    auto & et = entity->get<CTransform>();
    float speed = 30;
    auto bullet = m_entityManager.addEntity("bullet");
    bullet->add<CTransform>(et.pos, Vec2f( et.scale.x * speed, 0) , Vec2f(1, 1), et.angle);
    bullet->add<CAnimation>(Assets::Instance().getAnimation(m_playerConfig.WEAPON), true);
    bullet->add<CBoundingBox>( Assets::Instance().getAnimation(m_playerConfig.WEAPON).getSize() );
}

void Scene_Play::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sCollision();
    sLifespan();
    sAnimation();
    sGUI();
    sRender();
    m_currentFrame++;
}

void Scene_Play::sMovement()
{
    // TODO: Implement player movement / jumping based on its CInput component
    // TODO: Implement gravity's efect on the player
    // TODO: Implement the maximum player speed in both X and Y directions
    // NOTE: Setting an entity's scale.x to -1/1 will set facing to the left / right
    auto & transform = m_player->get<CTransform>();
    auto & state     = m_player->get<CState>();
    auto & input     = m_player->get<CInput>();
    
    if (input.up && input.canJump )    
    {
      transform.velocity.y = -m_playerConfig.JUMP;
      state.state = "jumping";
      input.canJump = false;
    }

    if (input.down)       transform.velocity.y =  m_playerConfig.JUMP;
    if (input.left)  
    {
      transform.velocity.x = -m_playerConfig.SPEED;
      if ( input.canJump )      state.state = "run";
    }
    else if (input.right)
    {
      transform.velocity.x =  m_playerConfig.SPEED;
      if ( input.canJump )     state.state = "run";
    }
    else               
    {
      transform.velocity.x = 0;
      state.state = "stand";
    }

    if (m_player->has<CGravity>())                            transform.velocity.y += m_player->get<CGravity>().gravity;
    if (transform.velocity.x > m_playerConfig.MAXSPEED)       transform.velocity.x = m_playerConfig.MAXSPEED; 
    if (transform.velocity.y > m_playerConfig.MAXSPEED)       transform.velocity.y = m_playerConfig.MAXSPEED; 

    transform.prevPos = transform.pos;
    transform.pos    += transform.velocity;

    // bullets 
    for ( auto b : m_entityManager.getEntities("bullet") )
    {
      auto & bt = b->get<CTransform>();
      bt.prevPos = bt.pos;
      bt.pos    += bt.velocity;
    }
}

void Scene_Play::sLifespan()
{
    // TODO: Check lifespawn of entities that have them, and destroy them if they go over
    for ( auto e : m_entityManager.getEntities() )
    {
      if ( e->has<CLifespan>() )
      {
        auto & lifespan = e->get<CLifespan>();
        int timeAlive   = m_currentFrame - lifespan.frameCreated;
        if ( timeAlive >= lifespan.lifespan )
        {
          e->destroy();
        }
      }
    }
}

void Scene_Play::sCollision()
{
    // REMEMBER: SFML's (0,0) position is on the TOP-LEFT corner
    //           This means jump will have a negative y-component
    //           and gravity will have a positive y-component
    //           Also, something BELOW something wlse will have a y value GREATER than it
    //           Also, something ABOVE something wlse will have a y value LESS than it

    // TODO: Implement Physics::GetOverlap() function, use it inside this function

    // TODO: Implement bullet / tile collisions
    //       Destroy the tile if it has a Brick animation
    // TODO: Implement player / tile collisions and resolutions
    //       Update the CState component of the player to store whether
    //       it is currently on the ground or in the air. This will be 
    //       used by the Animation system 
    // TODO: Check to see if the player has fallen down a hole (y > height())
    // TODO: Don't let the player walk off the left side of the map
  for ( auto e : m_entityManager.getEntities("tile") )
  {
    auto overlap         = Physics::GetOverlap(m_player, e);
    if ( overlap == Vec2f(0,0) ) continue;
    else
    {
      auto prevOverlap     = Physics::GetPreviousOverlap(m_player, e);

      // case where it player comes vertical 
      if ( prevOverlap.x > 0 )
      {
        // comes from above 
        if ( m_player->get<CTransform>().prevPos.y < e->get<CTransform>().prevPos.y )
        {
          m_player->get<CTransform>().velocity.y = 0;
          m_player->get<CTransform>().pos.y -= overlap.y;
          m_player->get<CInput>().canJump = true;
        }

        // comes from below
        if ( m_player->get<CTransform>().prevPos.y > e->get<CTransform>().prevPos.y )
        {
          m_player->get<CTransform>().velocity.y = 0;
          m_player->get<CTransform>().pos.y += overlap.y;
          if ( e->get<CAnimation>().animation.getName() == "Brick" )
          {
            auto explosion = m_entityManager.addEntity("explosion");
            explosion->add<CTransform>(e->get<CTransform>().pos);
            explosion->add<CAnimation>(Assets::Instance().getAnimation("Explosion"), false);
            e->destroy();
          }
          else if ( e->get<CAnimation>().animation.getName() == "Question" )
          {
            e->get<CState>().state = "hit";
          }
        }
      }
      // case where it comes horizontal
      else if ( prevOverlap.y > 0 )
      {
        // comes from left
        if ( m_player->get<CTransform>().prevPos.x < e->get<CTransform>().prevPos.x )
        {
          m_player->get<CTransform>().velocity.x = 0;
          m_player->get<CTransform>().pos.x -= overlap.x;
        }

        // comes from right
        if ( m_player->get<CTransform>().prevPos.x > e->get<CTransform>().prevPos.x )
        {
          m_player->get<CTransform>().velocity.x = 0;
          m_player->get<CTransform>().pos.x += overlap.x;
        }
      }
    } 
  }

  // Avoid going to the left
  if ( (m_player->get<CTransform>().pos.x - m_player->get<CBoundingBox>().halfSize.x) < 0 )
  {
    m_player->get<CTransform>().pos.x -= m_player->get<CTransform>().pos.x - m_player->get<CBoundingBox>().halfSize.x; 
  }

  // If player falls restart level
  if ( m_player->get<CTransform>().pos.y > m_game.window().getSize().y )
  {
    m_player->destroy();
    m_player = NULL;
    loadLevel(m_levelPath);
  }

  // bullets colliding 
  for ( auto b : m_entityManager.getEntities("bullet") )
  {
    for ( auto e : m_entityManager.getEntities("tile") )
    {
      auto overlap     = Physics::GetOverlap(b, e);
      if ( overlap == Vec2f(0, 0) ) continue;
      else
      {
        b->destroy();
        if ( e->get<CAnimation>().animation.getName() == "Brick" )
        {
          e->destroy();
        }
      }
    }
  }
}

void Scene_Play::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if      (action.name() == "GO_LEFT")              { m_player->get<CInput>().right = false; m_player->get<CInput>().left = true; m_player->get<CTransform>().scale.x = -1;}
        else if (action.name() == "GO_RIGHT")             { m_player->get<CInput>().left  = false; m_player->get<CInput>().right = true; m_player->get<CTransform>().scale.x = 1;}
        else if (action.name() == "GO_UP")                { m_player->get<CInput>().up   = true; }
        else if (action.name() == "GO_DOWN")              { m_player->get<CInput>().down = true; }
        else if (action.name() == "SHOOT")                { m_player->get<CInput>().shoot = true; m_player->get<CInput>().canShoot = false; spawnBullet(m_player);}
        else if (action.name() == "TOGGLE_TEXTURE")       { m_drawTextures = !m_drawTextures; }
        else if (action.name() == "TOGGLE_COLLISION")     { m_drawCollision = !m_drawCollision; }
        else if (action.name() == "TOGGLE_GRID")          { m_drawGrid = !m_drawGrid; }
        else if (action.name() == "PAUSED")               { setPaused(!m_paused); }
        else if (action.name() == "QUIT")                 { onEnd(); }
    }
    else if (action.type() == "END")
    {
        // these should be false
        if      (action.name() == "GO_LEFT")              { m_player->get<CInput>().left = false; }
        else if (action.name() == "GO_RIGHT")             { m_player->get<CInput>().right = false; }
        else if (action.name() == "GO_UP")            
        {
          m_player->get<CInput>().up   = false;
          if ( m_player->get<CTransform>().velocity.y < 0 )    m_player->get<CTransform>().velocity.y = 0; 
        }
        else if (action.name() == "GO_DOWN")              { m_player->get<CInput>().down = false; } 
        else if (action.name() == "SHOOT")                { m_player->get<CInput>().canShoot = true; }
    }
}

void Scene_Play::sAnimation()
{
    // TODO: Complete the Animation class code first

    // TODO: for each entity with an animation, call entity->get<CAnimation>().animation.update
    //       if the animation is not repeated, and it has ended, destroy the entity 
    for (auto e : m_entityManager.getEntities() )
    {
      if (e->has<CAnimation>())
      {
        if (e->get<CAnimation>().animation.getSpeed() != 0)
        {
          if (m_currentFrame % e->get<CAnimation>().animation.getSpeed() == 0)
          e->get<CAnimation>().animation.update();
        }
      }
    }

    // TODO: set the animation of the player based on its CState component
    // if the player's state has been set to running 
    if (m_player->get<CState>().state == "run")
    {
        // change its animation to a repeating run animation 
        // note: adding a component that already exists simply overwrites it 
        auto & animation             = m_player->get<CAnimation>().animation;
        if (animation.getName() != "Run" )
        animation         = Assets::Instance().getAnimation("Run");
    }
    if (m_player->get<CState>().state == "stand")
    {
        auto & animation  = m_player->get<CAnimation>().animation;
        animation         = Assets::Instance().getAnimation("Stand");
    }
}

void Scene_Play::onEnd()
{
    // TODO: When the scene ends, change back to the MENU scene
    //       use m_game.changeScene(correct params);
    //       Implement when Menu scene is implemented
    exit(1);
}

void Scene_Play::sGUI()
{
    ImGui::Begin("Scene Properties");
    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("Actions"))
        {
            for (const auto& [key, name] : getActionMap())
            {
                std::string ss = "START##" + name;
                std::string se = "END##" + name;

                if (ImGui::Button(ss.c_str()))
                {
                    doAction(Action(name, "START"));
                }
                ImGui::SameLine();
                if (ImGui::Button(se.c_str()))
                {
                    doAction(Action(name, "END"));
                }
                ImGui::SameLine();
                ImGui::Text("%s", name.c_str());
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Assets"))
        {
            if (ImGui::CollapsingHeader("Animations", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent();
                int count = 0;
                for (const auto& [name, anim] : Assets::Instance().getAnimations())
                {
                    count++;
                    ImGui::ImageButton(name.c_str(), anim.getSprite(), sf::Vector2f(32, 32));
                    //if ((count % 6) != 0 && count != Assets::Instance().getAnimations().size()) SOMETHING HERREEE
                }
                ImGui::Unindent();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}


void Scene_Play::sRender()
{
    // color the background darker so you know that the game is paused
    if (!m_paused) { m_game.window().clear(sf::Color(100, 100, 255)); }
    else { m_game.window().clear(sf::Color(50, 50, 150)); }

    sf::Text gridText(Assets::Instance().getFont("Grid"), "", 22);

    // set the viewport of the window to be centered on the player if it's far enough right 
    auto & pPos = m_player->get<CTransform>().pos;
    float windowCenterX = std::max(m_game.window().getSize().x / 2.0f, pPos.x);
    sf::View view = m_game.window().getView();
    view.setCenter({ windowCenterX, m_game.window().getSize().y - view.getCenter().y });
    m_game.window().setView(view);

    for (auto e : m_entityManager.getEntities())
    {
      auto & transform = e->get<CTransform>();
      // draw all entity collision bounding boxes with a rect shape
      if (m_drawCollision)
      {
       if (e->has<CBoundingBox>())
       {
            auto & box       = e->get<CBoundingBox>();
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(box.size.x + 1, box.size.y + 1));
            rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
            rect.setPosition( {transform.pos.x, transform.pos.y} );
            rect.setFillColor(sf::Color(0,0,0,0));
            rect.setOutlineColor(sf::Color(255, 255, 255, 255));
            rect.setOutlineThickness(1);
            m_game.window().draw(rect);
            
        }
      }

      // draw all Entity textures / animations
      if (m_drawTextures)
      { 
        if (e->has<CAnimation>())
        {
          sf::Sprite sprite = e->get<CAnimation>().animation.getSprite();
          auto &  animation = e->get<CAnimation>().animation;
          sprite.setRotation(sf::degrees(transform.angle));
          sprite.setOrigin(sf::Vector2f(animation.getSize().x / 2, 
                                        animation.getSize().y / 2));
          if (e->tag() == "player")
          {
            auto &  bb        = e->get<CBoundingBox>().size;
            sprite.setPosition({ transform.pos.x, transform.pos.y - (animation.getSize().y - bb.y) / 2 });
          }
          else
          {
            sprite.setPosition({transform.pos.x, transform.pos.y});
          }

          if (animation.getName() == "Question")
          {
            auto state = e->get<CState>().state;
            if (state == "noHit")
            {
              float factor = 0.15 * std::sin(0.10 * m_currentFrame) + 0.85;
              sprite.setColor(sf::Color(factor * 253, factor * 165, factor * 65));
            }
            if (state == "hit")
            {
              float factor = 0.5;
              sprite.setColor(sf::Color(factor * 253, factor * 165, factor * 65));
            }
          }
          sprite.setScale({transform.scale.x, transform.scale.y});
          m_game.window().draw(sprite);
        }
      }

    }

    // draw the grid so that students can easily debug
    if (m_drawGrid)
    {
        float leftX = m_game.window().getView().getCenter().x - m_game.window().getSize().x / 2;
        float rightX = leftX + m_game.window().getSize().x + m_gridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

        for (float x = nextGridX; x < rightX; x += m_gridSize.x)
        {
            drawLine(Vec2f(x, 0), Vec2f(x, m_game.window().getSize().y));
        }

        for (float y = 0; y < m_game.window().getSize().y; y += m_gridSize.y)
        {
            drawLine(Vec2f(leftX, m_game.window().getSize().y - y), Vec2f(rightX, m_game.window().getSize().y - y));

            for (float x = nextGridX; x < rightX; x += m_gridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
                std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
                gridText.setString("(" + xCell + "," + yCell + ")");
                gridText.setPosition({ x + 3, m_game.window().getSize().y - y - m_gridSize.y + 2});
                m_game.window().draw(gridText);
            }
        }
    }
}

void Scene_Play::drawLine(const Vec2f& p1, const Vec2f& p2)
{
    sf::Vertex line[] = { { {p1.x, p1.y}, sf::Color::White }, { {p2.x, p2.y}, sf::Color::White }};
    m_game.window().draw(line, 2, sf::PrimitiveType::Lines);
}

void Scene_Play::setPaused(bool paused)
{
    m_paused = paused;
}
