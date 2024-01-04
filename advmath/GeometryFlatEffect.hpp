#pragma once

#include "Pipeline.hpp"
#include "DefaultVertexShader.hpp"
#include "DefaultGeometryShader.hpp"

class GeometryFlatEffect
{
public:
    class Vertex
    {
    public:
        Vertex() = default;

        Vertex(const Vef3& pos)
            :
            pos(pos)
        {}
        Vertex(const Vef3& pos, const Vertex& src)
            :
            pos(pos)
        {}

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
        Triangle <Output> operator () (const VertexShader::Output& in0, const VertexShader::Output& in1, const VertexShader::Output& in2, size_t triangle_index) const
        {
            const auto n = ((in1.pos - in0.pos) % (in2.pos - in0.pos)).GetNormalized();
            const auto d = diffuse * std::max(0.0f, -n * dir);
            const auto c = Color(color.GetHadamard(d + ambient).Saturate() * 255.0f);

            return { {in0.pos, c}, {in1.pos, c}, {in2.pos, c} };
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

        Vef3 dir = { 0.0f,0.0f,1.0f };
        Vef3 diffuse = { 1.0f,1.0f,1.0f };
        Vef3 ambient = { 0.1f,0.1f,0.1f };
        Vef3 color = { 0.8f,0.85f,1.0f };
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