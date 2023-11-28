#pragma once

#include "Drawable.hpp"

class CoordinateTransformer
{
public:
    CoordinateTransformer(Graphics& in_gfx)
        :
        gfx(in_gfx)
    {

    }


public:
    void Draw(Drawable drawable) const
    {
        const Vef2 offset = { static_cast<float>(Graphics::ScreenWidth / 2), static_cast<float>(Graphics::ScreenHeight / 2) };

        drawable.ApplyTransformation(Maf3::Translater(offset) * Maf3::YFlipper());
        drawable.Render(gfx);
    }


private:
    Graphics& gfx;
};