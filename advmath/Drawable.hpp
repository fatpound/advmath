#pragma once

#include "Vec2.hpp"
#include "Graphics.h"

class Drawable
{
public:
    Drawable(const std::vector<Vef2>& in_model, const Maf3& transformer, Color in_color)
        :
        model(&in_model),
        transformation(transformer * Maf3::Identity()),
		color(in_color)
    {

    }


public:
    void ApplyTransformation(const Maf3& transformer)
    {
        transformation = transformer * transformation;
    }
    void Render(Graphics& gfx) const
    {
        gfx.DrawClosedPolyLine(*model, transformation, color);
    }


private:
    const std::vector<Vef2>* model = nullptr;

    Maf3 transformation = Maf3::Identity();
    Color color;
};