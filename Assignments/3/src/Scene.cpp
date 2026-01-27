#include "Scene.h"



void Scene::simulate(int nSimulations)
{
    // TODO
    return;
}





class Scene
{
    GameEngine&                            m_game;
    EntityManager                          m_entities;
    int                                    m_frame;
    std::map<int, const std::string&>      m_actionMap;
    bool                                   m_paused;
public:
    void update() = 0;
    void sDoAction(const Action& action) = 0;
    void sRender() = 0;

    //void simulate(int nSimulations);
    void doAction(const Action& action);
    void registerAction(int inputKey, const std::string& aName);
}