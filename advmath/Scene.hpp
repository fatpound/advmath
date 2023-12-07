#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Graphics.hpp"

class Scene
{
public:
    virtual ~Scene() = default;


public:
    virtual void Update(Keyboard& kbd, Mouse& mouse, float deltaTime) = 0;
    virtual void Draw(Graphics& gfx) const = 0;
};