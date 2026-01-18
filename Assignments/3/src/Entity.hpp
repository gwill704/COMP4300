#pragma once

#include "Components.hpp"
#include "memroy"


class Entity 
{
    bool                        m_active          ;
    int                         m_id              ;
    std::string                 m_tag             ;
    std::vector<Component>      m_components      ; 
public:
    
}