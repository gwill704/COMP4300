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

void ScenePlay::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::Scancode::P,       "PAUSE");
    registerAction(sf::Keyboard::Scancode::Escape,  "QUIT");
    registerAction(sf::Keyboard::Scancode::T,       "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::Scancode::C,       "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::Scancode::g,       "TOGGLE_GRID");

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

    return Vec2f(0, 0);
}

void Scene_Play::loadLevel(const std::string& filename)
{
    // reset the entity mangaer every time we load a level 
    m_entityManager = EntityManager();

    // TODO: read in the level file and add the appropiae entities
    //       use the PlayerConfig struct m_playerConfig to store player properties
    //       this struct is defined at the top of Scene_Play.h

    // Note: all of the code below is a sample code which shows you how to 
    //       set up and use entities it should be removed

    spawnPlayer();

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
    block->add<CBoundingBox>(sf::Vector2f(Assets::Instance().getAnimation("Block").getRect().size));

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
    //       auto& transform2 = entity->get<CTransform>()
}

void Scene_Play::spawnPlayer()
{
    // check to see if a player already exists before adding a new one 
    // if it already exists, just overwrite the values of the existing one
    if (!m_player) { m_player = m_entityManager.addEntity("player"); }

    // here is a sample player entity which you can use to construct other entities
    m_player->add<CAnimation>(Assets::Instance().getAnimation("Stand"), true);
    m_player->add<CTransform>(Vec2f(224, 352)); 
    m_player->add<CBoundingBox>(Vec2f(48,48));
    m_player->add<CState>("stand");
    m_player->add<CInput>();

    // TODO: be sure to add the remaining components to the player
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
    // TODO: this should spawn a bullet at the given entity, 
    //       going in the direction the entity is facing 
}

void Scene_Play::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sGUI();
    sRender();
}

void Scene_Play::sMovement()
{
    // TODO: Implement player movement / jumping based on its CInput component
    // TODO: Implement gravity's efect on the player
    // TODO: Implement the maximum player speed in both X and Y directions
    // NOTE: Setting an entity's scale.x to -1/1 will set facing to the left / right
}

void Scene_Play::sLifespan()
{
    // TODO: Check lifespawn of entities that have them, and destroy them if they go over
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
}

void Scene_Play::sdoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "TOGGLE_TEXTURE")          { m_drawTextures = !m_drawTextures; }
        else if (action.name == "TOGGLE_COLLISION")     { m_drawCollision = !m_drawCollision; }
        else if (action.name == "TOGGLE_COLLISION")     { m_drawCollision = !m_drawCollision; }
        else if (action.name == "TOGGLE_GRID")          { m_drawGrid = !m_drawGrid; }
        else if (action.name == "PAUSED")               { setPaused(!m_paused); }
        else if (action.name == "QUIT")                 { onEnd(); }
        else if (action.name == "RIGHT")                { m_player->get<CInput>().right = true; }
    }
    else if (action.type() == "END")
    {
        // these should be false
    }
}

void Scene_Play::sAnimation()
{
    // TODO: Complete the Animation class code first

    // TODO: for each entity with an animation, call entity->get<CAnimation>().animation.update
    //       if the animation is not repeated, and it has ended, destroy the entity 

    // TODO: set the animation of the player based on its CState component
    // if the player's state has been set to running 
    if (m_player->get<CState>().state == "run")
    {
        // change its animation to a repeating run animation 
        // note: adding a component that already exists simply overwrites it 
        m_player->add<CAnimation>(Assets::Instance().getAnimation("Run"), true);
    }
}

void Scene_Play::onEnd()
{
    // TODO: When the scene ends, change back to the MENU scene
    //       use m_game.changeScene(correct params);
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
            if (ImGui::CollapseHeader("Animations", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent();
                int count = 0;
                for (const auto& [name, anim] : Assets::Instance().getAnimations())
                {
                    count++;
                    ImGui::ImageButton(name.c_str(), anim.getSprite(), sf::Vector2f(32, 32));
                    if ((count % 6) != 0 && count != Assets::Instance().getAnimation().size())
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

    sf::Text gridText(Assets::Instance().getFont("Tech"), "", 12);

    // set the viewport of the window to be centered on the player if it's far enough right 
    auto & pPos = m_player->get<CTransform>().pos;
    float windowCenterX = std::max(m_game.window().getSize().x / 2.0f, pPos.x);
    sf::View view = m_game.window().getView();
    view.setCenter({ windowCenterX, m_game.window().getSize().y - view.getCenter().y });
    m_game.window().setView(view);

    // draw all Entity textures / animations
    if (m_drawTextures)
    {
        for (auto e : m_entityManager.getEntities())
        {
            auto & transform = e->get<CTransform>();

            if (e->has<CAnimation>())
            {
                sf::Sprite sprite = e->get<CAnimation>().animation.getSprite();
                sprite.setRotation(sf::degrees(transform.angle));
                sprite.setPosition(transform.pos);
                sprite.setScale(transform.scale);

                m_game.window().draw(sprite);
            }
        }
    }

    // draw all entity collision bounding boxes with a rect shape
    if (m_drawCollision)
    {
        for (auto e : m_entityManager.getEntities())
        {
            if (e->has<CBoundingBox>())
            {
                auto & box       = e->get<CBoundingBox>();
                auto & transform = e->get<CTransform>();
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
                rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
                rect.sePosition(transform.pos);
                rect.setFillColor(sf::Color(0,0,0,0));
                rect.setOutlineColor(sf::Color(255, 255, 255, 255));
                rect.setOutlineThickness(1);
                m_game.window().draw(rect);
            }
        }
    }

    // draw the grid so that students can easily debug
    if (m_drawGrid)
    {
        float leftX = m_game.window().getView().getCenter().x - width() / 2;
        float rightX = leftX + width() + m_gridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

        for (float x = nextGridX; x < rightX; x += m_gridSize.x)
        {
            drawLine(Vec2f(x, 0), Vec2f(x, height()));
        }

        for (float y = 0; y < height(); y += m_gridSize.y)
        {
            drawLine(Vec2f(leftX, height() - y), Vec2f(rightX, height() - y)):

            for (float x = nextGridX; x < rightX; x += m_gridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
                std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
                gridText.setString("(" + xCell + "," + yCell + ")");
                gridText.setPosition({ x + 3, height() - y - m_gridSize.y + 2});
                m_game.window().draw(gridText);
            }
        }
    }
}

void Scene_Play::drawLine(const Vec2f& p1, const Vec2f& p2)
{
    sf::Vertex line[] = { { p1, sf::Color::White }, { p2, sf::Color::White }};

    m_game.window().draw(line, 2, sf::PrimitiveTypes::Lines);
}