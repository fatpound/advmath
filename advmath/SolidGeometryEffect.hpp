#pragma once

#include "Pipeline.hpp"
#include "DefaultVertexShader.hpp"

class SolidGeometryEffect
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
            pos(in_pos)
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
    };

    typedef DefaultVertexShader<Vertex> VertexShader;

    class GeometryShader
    {
    public:
        class Output
        {
        public:
            Output() = default;

            Output(const Vef3& in_pos)
                :
                pos(in_pos)
            {

            }
            Output(const Vef3& in_pos, const Output& src)
                :
                pos(in_pos),
                color(src.color)
            {

            }
            Output(const Vef3& in_pos, const Color& color)
                :
                pos(in_pos),
                color(color)
            {

            }

        public:
            Output  operator  +  (const Output& rhs) const
            {
                return Output(*this) += rhs;
            }
            Output  operator  -  (const Output& rhs) const
            {
                return Output(*this) -= rhs;
            }
            Output  operator  *  (float rhs) const
            {
                return Output(*this) *= rhs;
            }
            Output  operator  /  (float rhs) const
            {
                return Output(*this) /= rhs;
            }
            Output& operator  += (const Output& rhs)
            {
                pos += rhs.pos;
                return *this;
            }
            Output& operator  -= (const Output& rhs)
            {
                pos -= rhs.pos;
                return *this;
            }
            Output& operator  *= (float rhs)
            {
                pos *= rhs;
                return *this;
            }
            Output& operator  /= (float rhs)
            {
                pos /= rhs;
                return *this;
            }

        public:
            Vef3 pos;
            Color color;
        };

    public:
        Triangle<Output> operator () (const VertexShader::Output& in0, const VertexShader::Output& in1, const VertexShader::Output& in2, size_t triangle_index) const
        {
            return{
                { in0.pos, triangle_colors[triangle_index / 2] },
                { in1.pos, triangle_colors[triangle_index / 2] },
                { in2.pos, triangle_colors[triangle_index / 2] }
            };
        };

        void BindColors(std::vector<Color> colors)
        {
            triangle_colors = std::move(colors);
        }

    private:
        std::vector<Color> triangle_colors;
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
    GeometryShader geometryshader;
    VertexShader vertexshader;
    PixelShader pixelshader;
};