#pragma once 

#include "GameEngine.h"
#include "Scene.h"
#include "Assets.h"

#include "EntityManager.hpp"


class Scene_Menu : public Scene
{
  protected:
    void init();
    enum Level { One, Two, Three };
    Level m_level;

  public:
    Scene_Menu(GameEngine& m_game);

    void update() override;
    void sDoAction(const Action& action) override; 
    void sRender() override; 
};
