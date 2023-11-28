#pragma once

#include "Vec2.hpp"
#include "Graphics.h"

class Drawable
{
public:
    Drawable(const std::vector<Vef2>& in_model, const Maf3& transformer, Color in_c)
        :
        model(&in_model),
        transformation(transformer * Maf3::Identity()),
        c(in_c)
    {

    }


public:
    void ApplyTransformation(const Maf3& transformer)
    {
        transformation = transformer * transformation;
    }
    void Render(Graphics& gfx) const
    {
        gfx.DrawClosedPolyLine(*model, transformation, c);
    }


private:
    const std::vector<Vef2>* model = nullptr;

    Maf3 transformation = Maf3::Identity();
    Color c;
};