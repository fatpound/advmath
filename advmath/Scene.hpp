#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Scene
{
public:
    virtual ~Scene() = default;


public:
    virtual void Update(Keyboard& kbd, Mouse& mouse, float deltaTime) = 0;
    virtual void Draw(Graphics& gfx) const = 0;
};