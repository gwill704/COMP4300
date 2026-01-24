#pragma once 

#include "Entity.hpp"

typedef EntityVec = std::vector<std::shared_ptr<Entity>>;
typedef EntityMap = std::map<std::string, EntityVec>;

class EntityManager
{
    EntityVec m_entities;
    EntityMap m_entityMap;
    EntityVec m_toAdd;
    size_t    m_totalEntities = 0;
public:

    EntityManager() {}

    std::shared_ptr<Entity> addEntity(std::string& tag)
    {
        auto e = std::make_shared<Entity>(tag, m_totalEntities++);
        m_toAdd.push_back(e);

        return e;
    }

    void update()
    {
        for (auto e : m_toAdd)
        {
            m_entities.push_back(e);
            m_entityMap[e->tag()].push_back(e);
        }
        m_toAdd.clear();

        for (auto it = m_entities.begin(); it != m_entities.end(); )
        {
            if (!(*it)->isActive())  it = m_entities.erase(it); 
            else                   ++it;
        }
    }

    EntityVec& getEntities()
    {
        return m_entities;
    }

    EntityVec& getEntities(const std::string& tag)
    {
        return m_entityMap[tag];
    }
}