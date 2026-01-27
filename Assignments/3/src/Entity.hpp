#pragma once

#include "Components.hpp"
#include "memory"
#include <tuple>

class EntityManager;

using ComponentTuple = std::tuple<
    CTransform, 
    CLifespan,
    CAnimation, 
    CBoundingBox,
    CInput, 
    CState,
    CGravity
>;

class Entity 
{
    friend class EntityManager;
    bool                        m_active = true   ;
    size_t                      m_id              ;
    const std::string           m_tag = "default" ;
    ComponentTuple              m_components      ; 
    Entity() = default;
    Entity(const std::string& tag, const size_t id)
    : m_tag(tag), m_id(id)  {}
public:


    template <typename T>
    T& get()
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    const T& get() const
    {
        return std::get<T>(m_components);
    }

    template <typename T, typename... TArgs>
    T& add(TArgs&&... mArgs)
    {
        auto & component = get<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.exists = true;
        return component;
    }

    template <typename T>
    bool has()
    {
        return get<T>().exists;
    }

    template <typename T>
    void remove()
    {
        get<T>() = T();
    }

    bool isActive() const
    {
        return m_active;
    }

    const std::string& tag() const
    {
        return m_tag;
    }

    size_t id() const
    {
        return m_id;
    }
};