#pragma once

#include "Pipeline.hpp"
#include "DefaultVertexShader.hpp"
#include "DefaultGeometryShader.hpp"

class SolidColorEffect
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

            return *this;
        }
        Vertex& operator -= (const Vertex& rhs)
        {
            pos -= rhs.pos;

            return *this;
        }
        Vertex& operator *= (float rhs)
        {
            pos *= rhs;

            return *this;
        }
        Vertex& operator /= (float rhs)
        {
            pos /= rhs;

            return *this;
        }

    public:
        Vef3 pos;
        Color color;
    };
    class PixelShader
    {
    public:
        template <class Input>
        Color operator () (const Input& in) const
        {
            return in.color;
        }
    };


public:
    typedef DefaultVertexShader<Vertex> VertexShader;
    typedef DefaultGeometryShader<VertexShader::Output> GeometryShader;


public:
    GeometryShader geometryshader;
    VertexShader vertexshader;
    PixelShader pixelshader;
};