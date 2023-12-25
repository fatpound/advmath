#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Graphics.hpp"

#include <string>

class Scene
{
public:
    virtual ~Scene() = default;

    Scene(const std::wstring& in_name)
        :
        name(in_name)
    {

    }


public:
    const std::wstring& GetName() const
    {
        return name;
    }

    virtual void Update(Keyboard& kbd, Mouse& mouse, float deltaTime) = 0;
    virtual void Draw(Graphics& gfx) const = 0;


private:
    std::wstring name;
};