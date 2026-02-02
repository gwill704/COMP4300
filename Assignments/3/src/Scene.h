#pragma once

class GameEngine;

#include "EntityManager.hpp"
#include "Action.hpp"
#include <map>

#include <imgui-SFML.h>
#include <imgui.h>

typedef std::map<int, std::string> ActionMap;

class Scene
{
protected: 
    GameEngine&                            m_game;
    EntityManager                          m_entityManager;
    int                                    m_frame;
    ActionMap                              m_actionMap;
    bool                                   m_paused;
public:
    Scene() = delete;
    Scene(GameEngine& game);

    virtual void update() = 0;
    virtual void sDoAction(const Action& action) = 0;
    virtual void sRender() = 0;

    void simulate(int nSimulations);
    void doAction(const Action& action);
    void registerAction(sf::Keyboard::Scan inputKey, const std::string& aName);
    const ActionMap& getActionMap();
};