#pragma once

#include "Pipeline.hpp"
#include "DefaultVertexShader.hpp"
#include "DefaultGeometryShader.hpp"

class VertexFlatEffect
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
            normal(src.normal)
        {

        }
        Vertex(const Vef3& in_pos, const Vef3& in_n)
            :
            pos(in_pos),
            normal(in_n)
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
            normal += rhs.normal;

            return *this;
        }
        Vertex& operator -= (const Vertex& rhs)
        {
            pos -= rhs.pos;
            normal -= rhs.normal;

            return *this;
        }
        Vertex& operator *= (float rhs)
        {
            pos *= rhs;
            normal *= rhs;

            return *this;
        }
        Vertex& operator /= (float rhs)
        {
            pos /= rhs;
            normal /= rhs;

            return *this;
        }

    public:
        Vef3 pos;
        Vef3 normal;
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
            Output(const Vef3& in_pos, const Color& in_color)
                :
                pos(in_pos),
                color(in_color)
            {

            }

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

                return *this;
            }
            Output& operator -= (const Output& rhs)
            {
                pos -= rhs.pos;

                return *this;
            }
            Output& operator *= (float rhs)
            {
                pos *= rhs;

                return *this;
            }
            Output& operator /= (float rhs)
            {
                pos /= rhs;

                return *this;
            }

        public:
            Vef3 pos;
            Color color;
        };

    public:
        Output operator () (const Vertex& v) const
        {
            const auto d = diffuse * std::max(0.0f, -(v.normal * rotation) * dir);
            const auto c = color.GetHadamard(d + ambient).Saturate() * 255.0f;

            return { v.pos * rotation + translation, Color(c) };
        }

        void BindRotation(const Maf3& in_rotation)
        {
            rotation = in_rotation;
        }
        void BindTranslation(const Vef3& in_translation)
        {
            translation = in_translation;
        }
        void SetDiffuseLight(const Vef3& c)
        {
            diffuse = { c.x, c.y, c.z };
        }
        void SetAmbientLight(const Vef3& c)
        {
            ambient = { c.x, c.y, c.z };
        }
        void SetLightDirection(const Vef3& dl)
        {
            assert(dl.LenSq() >= 0.001f);

            dir = dl.GetNormalized();
        }
        void SetMaterialColor(Color c)
        {
            color = Vef3(c);
        }

    private:
        Maf3 rotation;

        Vef3 translation;

        Vef3 dir     = {  0.0f,  0.0f,   1.0f };
        Vef3 diffuse = {  1.0f,  1.0f,   1.0f };
        Vef3 ambient = {  0.1f,  0.1f,   0.1f };
        Vef3 color   = {  0.8f,  0.85f,  1.0f };
    };

    typedef DefaultGeometryShader<VertexShader::Output> GeometryShader;

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
    VertexShader vertexshader;
    GeometryShader geometryshader;
    PixelShader pixelshader;
};