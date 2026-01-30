#pragma once 

#include "Entity.hpp"
#include <memory>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec>     EntityMap;

class EntityManager
{
    EntityVec m_entities;
    EntityMap m_entityMap;
    EntityVec m_toAdd;
    size_t    m_totalEntities = 0;
public:

    EntityManager()= default;

    std::shared_ptr<Entity> addEntity(const std::string& tag)
    {
        auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
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

    const EntityVec& getEntities() const
    {
        return m_entities;
    }

    const EntityVec& getEntities(const std::string& tag)
    {
        return m_entityMap[tag];
    }

    const EntityMap& getEntityMap()
    {
        return m_entityMap;
    }
};