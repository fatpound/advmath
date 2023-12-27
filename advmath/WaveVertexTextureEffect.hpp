#pragma once

#include "Pipeline.hpp"

class WaveVertexTextureEffect
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
            tc(src.tc)
        {

        }
        Vertex(const Vef3& in_pos, const Vef2& in_t)
            :
            pos(in_pos),
            tc(in_t)
        {

        }

    public:
        Vertex  operator+(const Vertex& rhs) const
        {
            return Vertex(*this) += rhs;
        }
        Vertex  operator-(const Vertex& rhs) const
        {
            return Vertex(*this) -= rhs;
        }
        Vertex  operator*(float rhs) const
        {
            return Vertex(*this) *= rhs;
        }
        Vertex  operator/(float rhs) const
        {
            return Vertex(*this) /= rhs;
        }

        Vertex& operator+=(const Vertex& rhs)
        {
            pos += rhs.pos;
            tc += rhs.tc;

            return *this;
        }
        Vertex& operator-=(const Vertex& rhs)
        {
            pos -= rhs.pos;
            tc -= rhs.tc;

            return *this;
        }
        Vertex& operator*=(float rhs)
        {
            pos *= rhs;
            tc *= rhs;

            return *this;
        }
        Vertex& operator/=(float rhs)
        {
            pos /= rhs;
            tc /= rhs;

            return *this;
        }

    public:
        Vef3 pos;
        Vef2 tc;
    };
    class VertexShader
    {
    public:
        typedef Vertex Output;

    public:
        Output operator () (const Vertex& in) const
        {
            Vef3 pos = in.pos * rotation + translation;

            pos.y += amplitude * std::sin(time * freqScroll + pos.x * freqWave);

            return Output( pos, in.tc );
        }

        void BindRotation(const Maf3& in_rotation)
        {
            rotation = in_rotation;
        }
        void BindTranslation(const Vef3& in_translation)
        {
            translation = in_translation;
        }
        void SetTime(float _time)
        {
            time = _time;
        }

    private:
        Maf3 rotation;
        Vef3 translation;

        float time = 0.0f;
        float freqWave = 10.0f;
        float freqScroll = 5.0f;
        float amplitude = 0.05f;
    };
    class PixelShader
    {
    public:
        template<class Input>
        Color operator () (const Input& in) const
        {
            return pTexture->GetPixel(
                (unsigned int)std::min(in.t.x * tex_width + 0.5f,  tex_xclamp),
                (unsigned int)std::min(in.t.y * tex_height + 0.5f, tex_yclamp)
            );
        }

        void BindTexture(const std::wstring& filename)
        {
            pTexture = std::make_unique<Surface>(Surface::FromFile(filename));

            tex_width  = float(pTexture->GetWidth());
            tex_height = float(pTexture->GetHeight());
            tex_xclamp = tex_width - 1.0f;
            tex_yclamp = tex_height - 1.0f;
        }

    private:
        std::unique_ptr<Surface> pTexture;

        float tex_width;
        float tex_height;
        float tex_xclamp;
        float tex_yclamp;
    };


public:
    VertexShader vertexshader;
    PixelShader pixelshader;
};