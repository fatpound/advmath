#pragma once

#include "Vec3.hpp"
#include "Graphics.hpp"

using fatpound::math::Vef3;

class CubeScreenTransformer
{
public:
    CubeScreenTransformer()
        :
        xFactor(static_cast<float>(Graphics::ScreenWidth) / 2.0f),
        yFactor(static_cast<float>(Graphics::ScreenHeight) / 2.0f)
    {

    }


public:
    Vef3& Transform(Vef3& v) const
    {
        const float zInv = 1.0f / v.z;

        v.x = ( v.x * zInv + 1.0f) * xFactor;
        v.y = (-v.y * zInv + 1.0f) * yFactor;

        return v;
    }
    Vef3 GetTransformed(const Vef3& v) const
    {
        Vef3 trans = v;

        return Transform(trans);
    }


private:
    float xFactor;
    float yFactor;
};