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

    template<typename T>
    T& get<T>()
    {
        return std::get<T>(m_components);
    }

    void add<T>()
    {
        if 
        std::tuple_cat(m_components, std::make_tuple)
    }

    bool has<T>()
    {
        if (&this.get<T> == nullptr) { return false }
        else { return true }
    }
}