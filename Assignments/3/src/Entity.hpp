#pragma once

#include "Components.hpp"
#include "memory"


class Entity 
{
    bool                        m_active          ;
    int                         m_id              ;
    std::string                 m_tag             ;
    std::tuple<>                m_components      ; 
public:
    Entity() {};

    template <typename T>
    T& get()
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
    bool has<T>()
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

    std::string& tag() const
    {
        return m_tag;
    }

    size_t id() const
    {
        return m_id;
    }
}