#pragma once

class GameEngine;

#include "EntityManager.hpp"
#include "Action.hpp"
#include <map>

class Scene
{
protected: 
    GameEngine*                            m_game;
    EntityManager                          m_entities;
    int                                    m_frame;
    std::map<int, const std::string&>      m_actionMap;
    bool                                   m_paused;
public:
    Scene() = default;
    Scene(GameEngine* game);

    virtual void update() = 0;
    virtual void sDoAction(const Action& action) = 0;
    virtual void sRender() = 0;

    void simulate(int nSimulations);
    void doAction(const Action& action);
    void registerAction(int inputKey, const std::string& aName);
};