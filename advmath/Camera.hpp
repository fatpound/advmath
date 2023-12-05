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

		const float diagonal = std::sqrt(
			fatpound::math::sq(static_cast<float>(Graphics::ScreenWidth  / 2 * zoom))
			+
			fatpound::math::sq(static_cast<float>(Graphics::ScreenHeight / 2 * zoom))
		);

        return RectF::FromCenter(
            pos,
            diagonal,
            diagonal
        );
    }
    Vef2 GetPos() const
    {
        return pos;
    }

	float GetAngle() const
	{
		return angle;
	}
    float GetScale() const
    {
        return scale;
    }

	void SetAngle(const float new_angle)
	{
		angle = new_angle;
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
        drawable.ApplyTransformation(Maf3::Rotater(angle) * Maf3::Scaler(scale) * Maf3::Translater(-pos));
        coordinateTransformer.Draw(drawable);
    }


protected:


private:
    CoordinateTransformer& coordinateTransformer;
    Vef2 pos = { 0.0f, 0.0f };

	float angle = 0.0f;
    float scale = 1.0f;
};