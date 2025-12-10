#include "Entity.h"

Entity::Entity(const size_t id, const std::string& tag)
{

}


bool Entity::isActive() const
{
    return 0;
}


const std::string& Entity::tag() const
{
    return m_tag;
}


const size_t Entity::id() const
{
    return 0;
}


void Entity::destroy()
{

}