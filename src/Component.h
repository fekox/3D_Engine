#pragma once

#include "Tools/DLL-Exp/dll-Exp-Inp.h"

class Entity;

class EXPORT Component
{
public:
    explicit Component(Entity* entity);
    virtual ~Component() = 0;
    Entity* entity;

protected:
};

