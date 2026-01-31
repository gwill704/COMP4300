#pragma once


#include "Scene.h"
#include "Assets.h"

#include "EntityManager.hpp"


class Scene_Play : public Scene
{
    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

protected:
    std::shared_ptr<Entity> m_player;
    std::string             m_levelPath;
    PlayerConfig            m_playerConfig;
    bool                    m_drawTextures  = true;
    bool                    m_drawCollision = false;
    bool                    m_drawGrid      = false;
    const Vec2f             m_gridSize  = { 64, 64 };

    void init(const std::string& levelPath);

    void loadLevel(const std::string& levelPath);

    void update();
    void sDoAction(const Action& action);
    void sRender();

    Vec2f gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

    void onEnd();
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);
    void setPaused(bool paused);
    void drawLine(const Vec2f& p1, const Vec2f& p2);

    void sMovement();
    void sLifespan();
    void sCollision();
    void sAnimation();
    void sGUI();
    

public: 
    Scene_Play(GameEngine* gameEngine, const std::string& levelPath);

};
