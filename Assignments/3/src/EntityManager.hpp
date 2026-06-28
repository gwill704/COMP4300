#pragma once 

#include "Entity.hpp"
#include <memory>
#include <vector>

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

        removeDeadEntities(m_entities);

        for (auto & [tag, entityVec] : m_entityMap)
        {
          removeDeadEntities(entityVec);
        }
    }

    void removeDeadEntities(EntityVec & vec)
    {
      for (auto it = vec.begin(); it != vec.end(); )
      {
          if (!(*it)->isActive())  it = vec.erase(it); 
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
