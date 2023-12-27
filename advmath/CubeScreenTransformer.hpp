#pragma once

#include "Vec3.hpp"
#include "Graphics.hpp"

class CubeScreenTransformer
{
public:
    CubeScreenTransformer()
        :
        xFactor(static_cast<float>(Graphics::ScreenWidth)  / 2.0f),
        yFactor(static_cast<float>(Graphics::ScreenHeight) / 2.0f)
    {

    }


public:
    template <class Vertex>
    Vertex& Transform(Vertex& v) const
    {
        const float zInv = 1.0f / v.pos.z;

        v *= zInv;

        v.pos.x = ( v.pos.x + 1.0f) * xFactor;
        v.pos.y = (-v.pos.y + 1.0f) * yFactor;

        v.pos.z = zInv;

        return v;
    }
    template <class Vertex>
    Vertex GetTransformed(const Vertex& v) const
    {
        Vertex trans = v;
        trans = Transform(trans);

        return trans;
    }


private:
    float xFactor;
    float yFactor;
};