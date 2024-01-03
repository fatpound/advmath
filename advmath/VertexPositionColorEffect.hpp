#pragma once

#include "Pipeline.hpp"
#include "DefaultGeometryShader.hpp"

class VertexPositionColorEffect
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
    class VertexShader
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
            Output(const Vef3& in_pos, const Vef3& in_color)
                :
                pos(in_pos),
                color(in_color)
            {

            }

        public:
            Output  operator +  (const Output& rhs) const
            {
                return Output(*this) += rhs;
            }
            Output  operator -  (const Output& rhs) const
            {
                return Output(*this) -= rhs;
            }
            Output  operator *  (float rhs) const
            {
                return Output(*this) *= rhs;
            }
            Output  operator /  (float rhs) const
            {
                return Output(*this) /= rhs;
            }

            Output& operator += (const Output& rhs)
            {
                pos += rhs.pos;
                color += rhs.color;

                return *this;
            }
            Output& operator -= (const Output& rhs)
            {
                pos -= rhs.pos;
                color -= rhs.color;

                return *this;
            }
            Output& operator *= (float rhs)
            {
                pos *= rhs;
                color *= rhs;

                return *this;
            }
            Output& operator /= (float rhs)
            {
                pos /= rhs;
                color /= rhs;

                return *this;
            }

        public:
            Vef3 pos;
            Vef3 color;
        };

    public:
        Output operator () (const Vertex& in) const
        {
            const auto pos = in.pos * rotation + translation;

            return Output{ pos, Vef3{ std::abs(pos.x), std::abs(pos.y), std::abs(pos.z) } * 255.0f };
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
    class PixelShader
    {
    public:
        template <class Input>
        Color operator () (const Input& in) const
        {
            return Color(in.color);
        }
    };


    typedef DefaultGeometryShader<VertexShader::Output> GeometryShader;


public:
    GeometryShader geometryshader;
    VertexShader vertexshader;
    PixelShader pixelshader;
};