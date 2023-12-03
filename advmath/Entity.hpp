#pragma once

#include "Drawable.hpp"

class Entity
{
public:
    Entity(std::vector<Vef2> in_model, const Vef2& in_pos = { 0.0f, 0.0f }, Color in_color = color::Yellow)
        :
        model( std::move(in_model) ),
        pos( in_pos ),
        color(in_color)
    {

    }


public:
    Drawable GetDrawable() const
    {
        return Drawable(model, Maf3::Translater(pos) * Maf3::Rotater(angle) * Maf3::Scaler(scale), color);
    }

    std::vector<Vef2>& GetModel()
    {
        return model;
    }

    Vef2 GetPos() const
    {
        return pos;
    }
    Color GetColor() const
    {
        return color;
    }

    float GetScale() const
    {
        return scale;
    }
    float GetAngle() const
    {
        return angle;
    }

    void SetPos(const Vef2& newPos)
    {
        pos = newPos;
    }
    void SetColor(Color in_color)
    {
        color = in_color;
    }
    void SetScale(const float s)
    {
        scale = s;
    }
    void SetAngle(const float s_angle)
    {
        angle = s_angle;
    }

    void TranslateBy(const Vef2& offset)
    {
        pos += offset;
    }


private:
    std::vector<Vef2> model;

    Vef2 pos = { 0.0f, 0.0f };
    Color color;

    float angle = 0.0f;
    float scale = 1.0f;
};