#pragma once

#include "CoordinateTransformer.hpp"
#include "RectF.hpp"

class Camera
{
public:
    Camera(CoordinateTransformer& in_coordinateTransformer)
        :
        coordinateTransformer( in_coordinateTransformer)
    {

    }


public:
    RectF GetViewportRect() const
    {
        const float zoom = 1.0f / scale;

        return RectF::FromCenter(
            pos,
            static_cast<float>(Graphics::ScreenWidth / 2 * zoom),
            static_cast<float>(Graphics::ScreenHeight / 2 * zoom)
        );
    }
    Vef2 GetPos() const
    {
        return pos;
    }
    float GetScale() const
    {
        return scale;
    }

    void SetScale(const float new_scale)
    {
        scale = new_scale;
    }

    void MoveBy(const Vef2& offset)
    {
        pos += offset;
    }
    void MoveTo(const Vef2& new_pos)
    {
        pos = new_pos;
    }

    void Draw(Drawable drawable) const
    {
        drawable.ApplyTransformation(Maf3::Scaler(scale) * Maf3::Translater(-pos));
        coordinateTransformer.Draw(drawable);
    }


protected:


private:
    CoordinateTransformer& coordinateTransformer;
    Vef2 pos = { 0.0f, 0.0f };

    float scale = 1.0f;
};