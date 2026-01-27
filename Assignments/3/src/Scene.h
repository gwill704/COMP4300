#pragma once

#include "GameEngine.h"
#include "EntityManager.hpp"
#include "Action.hpp"
#include <map>

class Scene
{
    GameEngine&                            m_game;
    EntityManager                          m_entities;
    int                                    m_frame;
    std::map<int, const std::string&>      m_actionMap;
    bool                                   m_paused;
public:
    Scene() = default;
    Scene(GameEngine& game);

    void update() = 0;
    void sDoAction(const Action& action) = 0;
    void sRender() = 0;

    void simulate(int nSimulations);
    void doAction(const Action& action);
    void registerAction(int inputKey, const std::string& aName);
};