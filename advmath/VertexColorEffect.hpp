#pragma once

#include "Pipeline.hpp"
#include "DefaultVertexShader.hpp"

class VertexColorEffect
{
public:
    class Vertex
    {
    public:
        Vertex() = default;
        Vertex(const Vef3& in_pos)
            :
            pos(in_pos)
        {

        }

    public:
        Vertex(const Vef3& in_pos, const Vertex& src)
            :
            pos(in_pos),
            color(src.color)
        {

        }
        Vertex(const Vef3& in_pos, const Vef3& in_color)
            :
            pos(in_pos),
            color(in_color)
        {

        }

    public:
        Vertex  operator +  (const Vertex& rhs) const
        {
            return Vertex(*this) += rhs;
        }
        Vertex  operator -  (const Vertex& rhs) const
        {
            return Vertex(*this) -= rhs;
        }
        Vertex  operator *  (float rhs) const
        {
            return Vertex(*this) *= rhs;
        }
        Vertex  operator /  (float rhs) const
        {
            return Vertex(*this) /= rhs;
        }

        Vertex& operator += (const Vertex& rhs)
        {
            pos += rhs.pos;
            color += rhs.color;

            return *this;
        }
        Vertex& operator -= (const Vertex& rhs)
        {
            pos -= rhs.pos;
            color -= rhs.color;

            return *this;
        }
        Vertex& operator *= (float rhs)
        {
            pos *= rhs;
            color *= rhs;

            return *this;
        }
        Vertex& operator /= (float rhs)
        {
            pos /= rhs;
            color /= rhs;

            return *this;
        }

    public:
        Vef3 pos;
        Vef3 color;
    };
    class PixelShader
    {
    public:
        template <class Input>
        Color operator () (const Input& in) const
        {
            return Color(in.color);
        }
    };


public:
    typedef DefaultVertexShader<Vertex> VertexShader;


public:
    VertexShader vertexshader;
    PixelShader pixelshader;
};