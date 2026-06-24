#include "Scene.h"
#include "GameEngine.h"


Scene::Scene(GameEngine& game) 
        : m_game(game) {}


void Scene::simulate(int nSimulations)
{
    // TODO EVERYTHING
    return;
}

void Scene::doAction(const Action& action)
{
    // TODO EVERYTHING
    sDoAction(action);
    return;
}

void Scene::registerAction(sf::Keyboard::Scan inputKey, const std::string& aName)
{
    m_actionMap[static_cast<int>(inputKey)] = aName;
    return;
}

const ActionMap& Scene::getActionMap()
{
    return m_actionMap;
}
