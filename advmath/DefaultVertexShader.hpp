#pragma once

#include "Vec3.hpp"
#include "Mat3.hpp"

using fatpound::math::Vef2;
using fatpound::math::Vef3;
using fatpound::math::Maf3;

template <class Vertex>
class DefaultVertexShader
{
public:
    typedef Vertex Output;


public:
    Output operator () (const Vertex& in) const
    {
        return Output{ in.pos * rotation + translation, in };
    }

    void BindRotation(const Maf3& in_rotation)
    {
        rotation = in_rotation;
    }
    void BindTranslation(const Vef3& in_translation)
    {
        translation = in_translation;
    }


private:
    Maf3 rotation;
    Vef3 translation;
};